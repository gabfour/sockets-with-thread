using Client.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Client.Services
{
    public class ClientService
    {
        private static string TAG = nameof(ClientService);
        #region "Singleton"

        private static ClientService _instance;
        public static ClientService Instance
        {
            get
            {
                if (_instance == null)
                    _instance = new ClientService();
                return _instance;
            }
        }

        private ClientService()
        { }
        #endregion

        private Network.Client _client;
        public Network.Client Client { get => _client; }
        public bool IsConnected { get => _client != null && _client.IsConnected; }
        private bool _running = false;
        public bool IsRunning { get => _running; }
        private Thread _backgroundJobClientListener;
        public bool IsBackgroundJobAlive { get => _backgroundJobClientListener?.IsAlive == true; }

        public async Task<bool> TryToConnectToTheServer(string host, int port)
        {
            _client = await Network.Client.ConnectToServer(host, port);
            return _client != null;
        }

        public bool StartListening()
        {
            if (!IsConnected)
            {
                Output.LogError(TAG, "Connection is closed");
                return false;
            }
            _running = true;
            _backgroundJobClientListener = new Thread(async () =>
            {
                Output.Log(TAG, "Starting the backgroung job");
                while (_running)
                {
                    if (!IsConnected) continue;
                    var message = _client.WaitReceiveMessage();
                    if (message == null) continue;
                    Output.Log(TAG,$"New message received : {message}");
                }
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
