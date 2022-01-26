using Client.Network.MessageModels;
using Client.Network.Messages;
using Client.Utils;
using Client.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Navigation;
using System.Windows.Threading;

namespace Client.ViewModels
{
    public class LoggedOutViewModel : AbstractViewModel
    {
        private static string TAG = "LoggedOutViewModel";

        public LoggedOutViewModel(Page page) : base(page)
        {
        }

        ~LoggedOutViewModel()
        {
            Network.Client.Instance?.RemoveListenerOnReceived(LoginMessage.ID, HandleLoginResponse);
        }

        private void HandleLoginResponse(object? modelObj)
        {
            if (modelObj == null) return;
            if (modelObj is LoginMessageModelInput)
            {
                Application.Current?.Dispatcher.Invoke(new Action(() => {
                    _page.NavigationService.Navigate(new LoggedInView()); 
                }));
            }
        }

        public string _host = "localhost";
        public string Host
        {
            get => _host; set
            {
                _host = value;
                NotifyPropertyChanged();
            }
        }

        public string _port = "3490";

        public string Port
        {
            get => _port; set
            {
                _port = value;
                NotifyPropertyChanged();
            }
        }



        public string _username = "Joueur";
        public string Username
        {
            get => _username; set
            {
                _username = value;
                NotifyPropertyChanged();
            }
        }

        private bool _isConnecting = false;

        public bool IsConnecting
        {
            get => _isConnecting;
            set
            {
                _isConnecting = value;
                NotifyPropertyChanged();
                NotifyPropertyChanged("EnableConnectBtn");
                NotifyPropertyChanged("ShowProgressBar");
            }
        }

        public bool EnableConnectBtn { get => !_isConnecting; }
        public Visibility ShowProgressBar { get => _isConnecting ? Visibility.Visible : Visibility.Hidden; }

        public ICommand OnConnectClicked
        {
            get => new CommandHandler(OnConnectClickedCommand, () => true);
        }

        private void OnConnectClickedCommand()
        {
            if (!int.TryParse(_port, out var port))
            {
                Output.LogError(TAG, "Incorrect port was given");
                return;
            }
            IsConnecting = true;
            Network.Client.ConnectToServer(_host, port).ContinueWith(x =>
            {
                IsConnecting = false;
                if (x.Result == null)
                {
                    Output.LogError(TAG, "Connection to the server failed");
                    return;
                }

                Network.Client.Instance.AddListenerOnReceived(LoginMessage.ID, HandleLoginResponse);

                if (Network.Client.Instance.StartListening())
                {
                    LoginMessage.SendLoginMessage(_username);
                }
            });
        }
    }
}
