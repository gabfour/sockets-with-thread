using Client.Network.MessageModels;
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

        public LoginMessage(Client client, JObject? json = null) : base(client, ID, json)
        {
        }
        public static void SendLoginMessage(string username)
        {
            var client = Client.Instance;
            var result = new LoginMessage(client)
            {
                Username = username
            };

            client.SendMessage(result);
        }
        public override MessageModelDefault? Deserialized()
        {
            LoginMessageModelInput? model = null;
            try
            {
                model = Json.ToObject<LoginMessageModelInput>();
            }
            catch
            {
                Output.LogError(TAG, "Error while parsing json");
                throw new Exception("Error while parsing json");
            }
            if (model == null)
            {
                throw new Exception("No error while parsing json");
            }
            Output.Log(TAG, $"<- Reponse: {model.username}");

            Client.Joueur.Username = model.username;

            return model;
            
        }

        public override MessageModelDefault Serialized()
        {
            var model = new LoginMessageModelOutput()
            {
                username = Username,
            };
            return model;
        }
    }
}
