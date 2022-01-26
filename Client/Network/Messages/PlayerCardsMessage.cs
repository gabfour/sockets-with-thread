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
    public class PlayerCardsMessage : DefaultMessage
    {
        public static string TAG = nameof(PlayerCardsMessage);
        public const int ID = 1;

        private string Username { get; set; } = string.Empty;

        public PlayerCardsMessage(Client client, JObject? json = null) : base(client, ID, json)
        {
        }
        public override MessageModelDefault? Deserialized()
        {
            PlayerCardsMessageInput? model = null;
            try
            {
                model = Json.ToObject<PlayerCardsMessageInput>();
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
            Output.Log(TAG, $"<- Reponse: {model.Cards.Count}");

            Client.Joueur.Cards = model.Cards;

            return model;

        }

        public override MessageModelDefault Serialized()
        {
            throw new NotImplementedException();
        }
    }
}
