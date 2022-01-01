using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private string _logMessages = "";
        public string LogMessages
        {
            get => _logMessages; set
            {
                _logMessages = $"{value}\n" + _logMessages;
                NotifyPropertyChanged();
            }
        }
        public MainWindow()
        {
            DataContext = this;
            InitializeComponent();
            //var tmp = new Thread(() =>
            //{
            //    while (true)
            //    {

            //        LogMessages = "Salut";
            //        Thread.Sleep(1000);
            //    }

            //});
            //tmp.Start();
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
        {
            var handler = PropertyChanged;
            if (handler != null)
                handler(this, new PropertyChangedEventArgs(propertyName));
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var client = new Thread(() =>
            {
                string targetedIp = "127.0.0.1";
                int port = 3490;
                //if (args == null || args.Length != 2 || !int.TryParse(args[1], out port))
                //{
                //    string file = typeof(Program).Assembly.Location;
                //    string appExeName = System.IO.Path.GetFileNameWithoutExtension(file);
                //    LogMessages = "Invalid parameters !";
                //    LogMessages = "program usage : " + appExeName + " server_address connection_port";
                //    return;
                //}
                LogMessages = "Trying to open connection to server " + targetedIp + " on the port " + port + "...";

                var s = OpenConnection(targetedIp, port);
                if (s == null)
                    return;
                LogMessages = "Connection to server opened successfully !";

                string buffer = null;
                while (true)
                {
                    //buffer = Console.ReadLine();

                    // Traitement de la chaîne lue
                    if (string.IsNullOrEmpty(buffer))
                        continue;
                    LogMessages = targetedIp + "> ";
                    if (buffer == "EXIT")
                        break;

                    // Envoi du buffer au serveur
                    Send(s, buffer);

                    // Lecture de la réponse du serveur
                    buffer = Receive(s);
                    if (string.IsNullOrEmpty(buffer))
                        continue;

                    // Traitement du résultat lu sur la socket
                    if (buffer == "CONNECTION_CLOSED")
                    {
                        LogMessages = "Server has closed connection !";
                        break;
                    }
                    else
                    {
                        // Affichage du message
                        LogMessages = buffer;
                    }
                }

                CloseConnection(s);
            });
            client.Start();
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
                //LogMessages = "Error while retreiving server ip from received server address : " + e.Message;
            }

            return "";
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
                //LogMessages = "Error while openning connection to server : " + e.Message);
            }
            return null;
        }

        private static bool CloseConnection(Socket s)
        {
            if (s != null && s.Connected)
            {
                try
                {
                    s.Shutdown(SocketShutdown.Both);
                    s.Close();
                    if (s.Connected)
                        WriteError("Error while closing socket : ");
                    else
                        return true;
                }
                catch (SocketException e)
                {
                    //LogMessages = "Error while closing socket : " + e.Message);
                }
            }
            return false;
        }

        private static string Receive(Socket s)
        {
            if (s == null || s.Connected || s.Poll(10, SelectMode.SelectRead) && s.Available == 0)
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                //LogMessages = "Connection to server has been closed.";
                return null;
            }

            // Attente de data à lire
            while (s.Available == 0) ;

            // Lecture des données
            string messageReceived = null;
            while (s.Available > 0)
            {
                try
                {
                    byte[] msg = new byte[s.Available];
                    //Réception des données
                    s.Receive(msg, 0, s.Available, SocketFlags.None);
                    var msgStr = System.Text.Encoding.UTF8.GetString(msg).Trim();
                    //On concatène les données reçues(max 4ko) dans
                    //une variable de la classe
                    messageReceived += msgStr;
                }
                catch (SocketException e)
                {
                    //LogMessages = "Error while receiving data on socket : " + e.Message);
                }
            }
            return messageReceived;
        }

        private static void Send(Socket s, string message)
        {
            if (string.IsNullOrEmpty(message))
                return;

            if (s == null || !s.Connected || !s.Poll(10, SelectMode.SelectWrite))
            {
                //La connexion a été clôturée par le serveur ou bien un problème
                //réseau est apparu
                //LogMessages = "Connection to server has been closed.";
                return;
            }

            byte[] msg = System.Text.Encoding.UTF8.GetBytes(message);

            try
            {
                s.Send(msg, msg.Length, SocketFlags.None);
            }
            catch (SocketException e)
            {
                //LogMessages = "Error while sending data on socket : " + e.Message);
            }
        }

        private static void WriteError(string description)
        {
            //LogMessages = description + Convert.ToString(System.Runtime.InteropServices.Marshal.GetLastWin32Error()));
        }
    }
}
