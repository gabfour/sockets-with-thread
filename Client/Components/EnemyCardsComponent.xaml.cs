using Client.Models;
using Client.Utils;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
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
    public partial class EnemyCardsHolderComponent : System.Windows.Controls.ListView, System.Windows.Markup.IComponentConnector
    {
        public EnemyCardsHolderComponent()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty NumberOfCardsProperty =
        DependencyProperty.Register(
            name: "NumberOfCards",
            propertyType: typeof(int),
            ownerType: typeof(EnemyCardsHolderComponent),
            typeMetadata: new FrameworkPropertyMetadata(defaultValue:0));

        public int NumberOfCards
        {
            get { return (int)GetValue(NumberOfCardsProperty); }
            set { SetValue(NumberOfCardsProperty, value);
                var result = new List<int>();
                for (var i = 0;i < value; i++)
                {
                    result.Add(i);
                }
                Cards = result;
            }
        }


        public static readonly DependencyProperty CardsProperty =
        DependencyProperty.Register(
            name: "Cards",
            propertyType: typeof(List<int>),
            ownerType: typeof(EnemyCardsHolderComponent),
            typeMetadata: new FrameworkPropertyMetadata(defaultValue: new List<int>()));

        public List<int> Cards
        {
            get { return (List<int>)GetValue(CardsProperty); }
            set { SetValue(CardsProperty, value); }
        }

        public static readonly DependencyProperty OrientationProperty =
        DependencyProperty.Register(
            name: "Orientation",
            propertyType: typeof(Orientation),
            ownerType: typeof(EnemyCardsHolderComponent),
            typeMetadata: new FrameworkPropertyMetadata(defaultValue: Orientation.Horizontal));

        public Orientation Orientation
        {
            get { return (Orientation)GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); 
            }
        }


        public int WidthThumb
        {
            get { return Orientation == Orientation.Horizontal ? 25 : 37; }
        }

        public int HeightThumb
        {
            get { return Orientation == Orientation.Horizontal ? 37 : 25; }
        }
    }
}
