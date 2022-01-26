using Client.Models;
using Client.Network.MessageModels;
using Client.Network.Messages;
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

        public List<Card> Cards { get => Network.Client.Instance?.Joueur.Cards ?? new List<Card>(); }

        public LoggedInViewModel(Page page) : base(page)
        {
            Network.Client.Instance?.AddListenerOnReceived(PlayerCardsMessage.ID, HandlePlayerCardResponse);
        }

        ~LoggedInViewModel()
        {
            Network.Client.Instance?.RemoveListenerOnReceived(PlayerCardsMessage.ID, HandlePlayerCardResponse);
        }

        private void HandlePlayerCardResponse(object? modelObj)
        {
            if (modelObj == null) return;
            if (modelObj is PlayerCardsMessageInput)
            {
                NotifyPropertyChanged("Cards");
            }
        }
        //private string _logs = string.Empty;
        //public string Logs
        //{
        //    get => _logs;
        //    set
        //    {
        //        _logs = value;
        //        NotifyPropertyChanged();
        //    }
        //}

        //public string Username
        //{
        //    get => Network.Client.Instance.Joueur.Username;
        //}

        //private string _command = string.Empty;
        //public string Command
        //{
        //    get => _command;
        //    set
        //    {
        //        _command = value;
        //        NotifyPropertyChanged();
        //    }
        //}

        //public ICommand OnDisconnectClickedCommand
        //{
        //    get => new CommandHandler(OnDisconnectClicked, () => true);
        //}

        //public ICommand OnCommandSendClickedCommand
        //{
        //    get => new CommandHandler(OnCommandSendClicked, () => true);
        //}

        //public LoggedInViewModel(Page page) : base(page)
        //{
        //    Output.OutputEventHandler += HandlerLogs;

        //}

        //~LoggedInViewModel()
        //{
        //    Output.OutputEventHandler -= HandlerLogs;
        //}

        //private void HandlerLogs(object? sender, string e)
        //{
        //    Application.Current?.Dispatcher.Invoke(new Action(() =>
        //    {
        //        Logs += $"{e}\n";
        //    }));
        //}

        //public void OnDisconnectClicked()
        //{
        //    if (Network.Client.Instance.IsConnected)
        //    {
        //        Network.Client.Instance.CloseConnection();
        //    }
        //    Output.OutputEventHandler -= HandlerLogs;
        //    Network.Client.Instance.StopListening();
        //    Application.Current?.Dispatcher.Invoke(new Action(() => { _page.NavigationService.GoBack(); }));
        //}

        //public void OnCommandSendClicked()
        //{
        //    if (!Network.Client.Instance.IsConnected)
        //    {
        //        Output.LogError(TAG, "Client is disconnected");
        //        return;
        //    }
        //    //ClientService.Instance.Client.SendMessage(Command).ContinueWith(x =>
        //    //{
        //    //    if (!x.Result)
        //    //    {
        //    //        Output.LogError(TAG, "Error while sending message");
        //    //    }
        //    //});
        //    Command = string.Empty;
        //}
    }
}
