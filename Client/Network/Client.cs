using Client.Models;
using Client.Network.Messages;
using Client.Utils;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Client.Network
{
    public class Client
    {
        private static string TAG = "Client";

        #region "Singleton"


        private static Client _instance;
        public static Client Instance
        {
            get
            {
                if (_instance == null)
                    throw new Exception("Singleton not initialized, please use Client.ConnectToServer");
                return _instance;
            }
        }

        #endregion

        #region "Static"
        public static Task<Client?> ConnectToServer(string ip, int port)
        {
            if (_instance?.IsConnected == true)
            {
                Output.Log(TAG, "Already connected");
                return Task<Client?>.Factory.StartNew(() =>  _instance);
            }
            return Task<Client?>.Factory.StartNew(() =>
            {
                var socket = OpenConnection(ip, port);
                if (socket == null) return null;
                Output.Log(TAG, "Connected to the server");
                _instance =  new Client(socket);
                return _instance;
            });
            
        }


        private static Socket OpenConnection(string serverAddress, int connectionPort)
        {
            Socket s;
            IPAddress ip = IPAddress.Parse(GetAddress(serverAddress));
            IPEndPoint ipEnd = new IPEndPoint(ip, connectionPort);
            s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                s.Connect(ipEnd);
                if (s.Connected)
                    return s;
            }
            catch (SocketException e)
            {
                Output.LogError(TAG, "Error while openning connection to server : " + e.Message);
            }
            return null;
        }

        private static string? GetAddress(string serverAddress)
        {
            try
            {
                IPHostEntry iphostentry = Dns.GetHostEntry(serverAddress);
                return iphostentry.AddressList.FirstOrDefault(ip => ip.AddressFamily == AddressFamily.InterNetwork)?.ToString();
            }
            catch (SocketException e)
            {
                Output.LogError(TAG, "Error while retreiving server ip from received server address : " + e.Message);
            }

            return "";
        }

        #endregion


        private Socket _socket;
        public bool IsConnected { get => _socket != null && _socket.Connected && !_socket.Poll(10, SelectMode.SelectRead); }

        private bool _running = false;
        public bool IsRunning { get => _running; }

        private Thread? _backgroundJobClientListener = null;
        public bool IsBackgroundJobAlive { get => _backgroundJobClientListener?.IsAlive == true; }


        private Dictionary<int, List<Action<object?>>> _onMessageReceived = new Dictionary<int, List<Action<object?>>>();
        public Joueur Joueur { get; private set; }


        public Client(Socket socket)
        {
            Joueur = new Joueur();
            _socket = socket;
        }

        public Task<bool> CloseConnection()
        {
            return Task<bool>.Factory.StartNew(() =>
            {
                if (_socket != null && _socket.Connected)
                {
                    try
                    {
                        _socket.Shutdown(SocketShutdown.Both);
                        _socket.Close();
                        if (_socket.Connected)
                            Output.LogError(TAG, "Error while closing socket");
                        else
                            return true;
                    }
                    catch (SocketException e)
                    {
                        Output.LogError(TAG, "Error while closing socket : " + e.Message);
                    }
                }
                return false;
            });
        }

        public string? WaitReceiveMessage()
        {
            if (_socket == null || !_socket.Connected || _socket.Poll(10, SelectMode.SelectRead))
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                Output.LogError(TAG, "Connection to server has been closed.");
                return null;
            }

            // Attente de data à lire
            for (var i = 10; _socket?.Connected == true && _socket.Available == 0 && i > 0; i--)
                Thread.Sleep(100);

            // Lecture des données
            string messageReceived = String.Empty;
            while (_socket?.Connected == true && _socket.Available > 0)
            {
                try
                {
                    byte[] msg = new byte[_socket.Available];
                    //Réception des données
                    _socket.Receive(msg, 0, _socket.Available, SocketFlags.None);
                    var msgStr = System.Text.Encoding.UTF8.GetString(msg).Trim();
                    //On concatène les données reçues(max 4ko) dans
                    //une variable de la classe
                    messageReceived += msgStr;
                }
                catch (SocketException e)
                {
                    Output.LogError(TAG, "Error while receiving data on socket : " + e.Message);
                }
            }
            return messageReceived;
        }

        public Task<bool> SendMessage(DefaultMessage message)
        {
            return Task<bool>.Factory.StartNew(() => {
                var model = message.Serialized();
                model.id = message.Id;
                var content = JsonConvert.SerializeObject(model);
                if (string.IsNullOrEmpty(content))
                    return false;

                if (_socket == null || !_socket.Connected || !_socket.Poll(10, SelectMode.SelectWrite))
                {
                    //La connexion a été clôturée par le serveur ou bien un problème
                    //réseau est apparu
                    Output.LogError(TAG, "Connection to server has been closed.");
                    return false;
                }

                byte[] msg = System.Text.Encoding.UTF8.GetBytes(content);

                try
                {
                    var nbr = _socket.Send(msg, msg.Length, SocketFlags.None);
                    Output.Log(TAG, $"-> Message send : {content}");
                    return nbr != 0;
                }
                catch (SocketException e)
                {
                    Output.LogError(TAG, "Error while sending data on socket : " + e.Message);
                }
                return false;
            });
            
        }


        public void AddListenerOnReceived(int idMessage, Action<object?> action)
        {
            List<Action<object?>> actions = new List<Action<object?>>();
            if (_onMessageReceived.ContainsKey(idMessage))
            {
                actions = _onMessageReceived[idMessage];
            }
            if (actions.Contains(action))
            {
                return;
            }
            actions.Add(action);
            _onMessageReceived.Remove(idMessage);
            _onMessageReceived.Add(idMessage, actions);
        }

        public void RemoveListenerOnReceived(int idMessage, Action<object?> action)
        {
            if (!_onMessageReceived.ContainsKey(idMessage))
            {
                return;
            }
            var actions = _onMessageReceived[idMessage];
            if (!actions.Contains(action))
            {
                return;
            }
            actions.Remove(action);
            _onMessageReceived.Remove(idMessage);
            _onMessageReceived.Add(idMessage, actions);
        }

        public bool StartListening()
        {
            if (!IsConnected)
            {
                Output.LogError(TAG, "Connection is closed");
                return false;
            }
            if (_running)
            {
                Output.Log(TAG, "Backgroung job already started");
                return true;
            }
            _running = true;
            _backgroundJobClientListener = new Thread(async () =>
            {
                Output.Log(TAG, "Starting the backgroung job");
                while (_running)
                {
                    if (!IsConnected) continue;
                    var buffer = WaitReceiveMessage();
                    if (buffer == null) continue;
                    if (buffer.Length == 0) break;
                    Output.Log(TAG, $"<- Message received : {buffer}");
                    var message = DefaultMessage.HandleMessage(this, buffer);
                    if (message == null) continue;
                    var model = message.Deserialized();
                    if (_onMessageReceived.ContainsKey(message.Id))
                    {
                        _onMessageReceived[message.Id].ForEach(x => Task.Factory.StartNew(() => x.Invoke(model)));
                    }
                }
                _running = false;
                Output.Log(TAG, "Backgroung job stopped");
            });
            _backgroundJobClientListener.Start();
            return true;
        }

        public void StopListening()
        {
            _running = false;
        }
    }
}
