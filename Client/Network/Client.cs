using Client.Utils;
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
        #region "Static"
        public static Task<Client> ConnectToServer(string ip, int port)
        {
            return Task<Client>.Factory.StartNew(() =>
            {
                var socket = OpenConnection(ip, port);
                if (socket == null) return null;
                return new Client(socket);
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

        private static string GetAddress(string serverAddress)
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

        public Client(Socket socket)
        {
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
            return String.IsNullOrEmpty(messageReceived) ? null : messageReceived;
        }

        public Task<bool> SendMessage(string message)
        {
            return Task<bool>.Factory.StartNew(() => {
                if (string.IsNullOrEmpty(message))
                    return false;

                if (_socket == null || !_socket.Connected || !_socket.Poll(10, SelectMode.SelectWrite))
                {
                    //La connexion a été clôturée par le serveur ou bien un problème
                    //réseau est apparu
                    Output.LogError(TAG, "Connection to server has been closed.");
                    return false;
                }

                byte[] msg = System.Text.Encoding.UTF8.GetBytes(message);

                try
                {
                    var nbr = _socket.Send(msg, msg.Length, SocketFlags.None);
                    return nbr != 0;
                }
                catch (SocketException e)
                {
                    Output.LogError(TAG, "Error while sending data on socket : " + e.Message);
                }
                return false;
            });
            
        }
    }
}
