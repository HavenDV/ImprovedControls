using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class IndicatorControl : UserControl
    {
        public string SliderName
        {
            get { return nameLabel.Text; }
            set { nameLabel.Text = value; }
        }

        public string SliderValue {
            get { return valueLabel.Text; }
            set { valueLabel.Text = value; }
        }

        public IndicatorControl()
        {
            InitializeComponent();
        }

        private void Slider_Paint(object sender, PaintEventArgs e)
        {
            var polygonWidth = Height;
            var polygon = new Point[] {
                new Point(0, 0),
                new Point(Width - polygonWidth, 0),
                new Point(Width, Height / 2),
                new Point(Width - polygonWidth, Height - 1),
                new Point(0, Height - 1),
            };
            using (var brush = new SolidBrush(Color.GreenYellow))
            {
                e.Graphics.FillPolygon(brush, polygon);
            }

            using (var pen = new Pen(Color.Black, 1))
            {
                e.Graphics.DrawPolygon(pen, polygon);
            }
        }
    }
}
