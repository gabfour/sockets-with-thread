using Client.Models;
using Client.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client.Components
{
    /// <summary>
    /// Interaction logic for CardsHolderComponent.xaml
    /// </summary>
    public partial class CardsHolderComponent : System.Windows.Controls.ListView, System.Windows.Markup.IComponentConnector
    {
        public CardsHolderComponent()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty CardsProperty =
        DependencyProperty.Register(
            name: "Cards",
            propertyType: typeof(List<Card>),
            ownerType: typeof(CardsHolderComponent),
            typeMetadata: new FrameworkPropertyMetadata(defaultValue:new List<Card>()));

        public List<Card> Cards
        {
            get { return (List<Card>)GetValue(CardsProperty); }
            set { SetValue(CardsProperty, value); }
        }
    }
}
