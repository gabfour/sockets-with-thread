using Client.Network.Messages;
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
        private Dictionary<int, List<Action<object?>>> _onMessageReceived = new Dictionary<int, List<Action<object?>>>();

        public async Task<bool> TryToConnectToTheServer(string host, int port)
        {
            _client = await Network.Client.ConnectToServer(host, port);
            return _client != null;
        }

        public void AddListener(int id, Action<object?> action)
        {
            List<Action<object?>> actions = new List<Action<object?>>();
            if (_onMessageReceived.ContainsKey(id))
            {
                actions = _onMessageReceived[id];
            }
            if (actions.Contains(action))
            {
                return;
            }
            actions.Add(action);
            _onMessageReceived.Remove(id);
            _onMessageReceived.Add(id, actions);
        }

        public void RemoveListener(int id, Action<object?> action)
        {
            if (!_onMessageReceived.ContainsKey(id))
            {
                return;
            }
            var actions = _onMessageReceived[id];
            if (!actions.Contains(action))
            {
                return;
            }
            actions.Remove(action);
            _onMessageReceived.Remove(id);
            _onMessageReceived.Add(id, actions);
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
                    var buffer = _client.WaitReceiveMessage();
                    if (buffer == null) continue;
                    Output.Log(TAG, $"New message received : {buffer}");
                    var message = DefaultMessage.HandleMessage(_client, buffer);
                    if (message == null) continue;
                    var model = message.Deserialized();
                    if (_onMessageReceived.ContainsKey(message.Id))
                    {
                        _ = Task.Factory.StartNew(() => _onMessageReceived[message.Id].ForEach(x =>
                        {
                            try
                            {
                                x.Invoke(model);
                            }
                            catch { }
                        }));
                    }
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
