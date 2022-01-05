using Client.Network.MessageModels;
using Client.Services;
using Client.Utils;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client.Network.Messages
{
    public class LoginMessage : DefaultMessage
    {
        public static string TAG = nameof(LoginMessage);
        public const int ID = 0;

        private string Username { get; set; } = string.Empty;
        private string Password { get; set; } = string.Empty;

        public LoginMessage(Client client, JObject json) : base(client, ID, json)
        {
        }
        public static void SendLoginMessage(string username, string password)
        {
            var client = ClientService.Instance.Client;
            var result = new LoginMessage(client, new JObject());

            result.Username = username;
            result.Password = password;

            client.SendMessage(result.Serialized());
        }
        public override object? Deserialized()
        {
            LoginMessageModelInput? model = null;
            try
            {
                model = Json.ToObject<LoginMessageModelInput>();
            }
            catch
            { 
            }
            if (model == null)
            {
                Output.LogError(TAG, "Error while parsing json");
                return null;
            }
            Output.Log(TAG, $"Reponse: {model.message}");

            return model;
            
        }

        public override string Serialized()
        {
            var model = new LoginMessageModelOutput()
            {
                id = ID,
                username = Username,
                password = Password
            };
            return JsonConvert.SerializeObject(model);
        }
    }
}
