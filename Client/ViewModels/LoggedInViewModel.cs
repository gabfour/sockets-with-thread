using Client.Services;
using Client.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Client.ViewModels
{
    public class LoggedInViewModel : AbstractViewModel
    {
        private static string TAG = nameof(LoggedInViewModel);
        private string _logs = string.Empty;
        public string Logs
        {
            get => _logs;
            set
            {
                _logs = value;
                NotifyPropertyChanged();
            }
        }


        private string _json = string.Empty;
        public string JSonMessage
        {
            get => _json;
            set
            {
                _json = value;
                NotifyPropertyChanged();
            }
        }

        private string _command = string.Empty;
        public string Command
        {
            get => _command;
            set
            {
                _command = value;
                NotifyPropertyChanged();
            }
        }

        public ICommand OnDisconnectClickedCommand
        {
            get => new CommandHandler(OnDisconnectClicked, () => true);
        }

        public ICommand OnCommandSendClickedCommand
        {
            get => new CommandHandler(OnCommandSendClicked, () => true);
        }

        public LoggedInViewModel(Page page) : base(page)
        {
            Output.OutputEventHandler += HandlerLogs;
            ClientService.Instance.StartListening();

        }

        ~LoggedInViewModel()
        {
            Output.OutputEventHandler -= HandlerLogs;
            ClientService.Instance.StopListening();
        }

        private void HandlerLogs(object? sender, string e)
        {
            Application.Current?.Dispatcher.Invoke(new Action(() =>
            {
                Logs += $"{e}\n";
            }));
        }

        public void OnDisconnectClicked()
        {
            if (ClientService.Instance.IsConnected)
            {
                ClientService.Instance.Client.CloseConnection();
            }
            Output.OutputEventHandler -= HandlerLogs;
            ClientService.Instance.StopListening();
            Application.Current?.Dispatcher.Invoke(new Action(() => { _page.NavigationService.GoBack(); }));
        }
        
        public void OnCommandSendClicked()
        {
            if (!ClientService.Instance.IsConnected)
            {
                Output.LogError(TAG, "Client is disconnected");
                return;
            }
            ClientService.Instance.Client.SendMessage(Command).ContinueWith(x =>
            {
                if (!x.Result)
                {
                    Output.LogError(TAG, "Error while sending message");
                }
            });
            Command = string.Empty;
        }
    }
}
