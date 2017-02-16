using System.Drawing;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class Slider : UserControl
    {
        public Slider()
        {
            InitializeComponent();
        }

        private void Slider_Paint(object sender, PaintEventArgs e)
        {
            var triangleWidth = Height;
            var triangle = new Point[] { new Point(Width - triangleWidth, 0), new Point(Width - triangleWidth, Height), new Point(Width, Height / 2) };
            var rect = new Rectangle(0, 0, Width - triangleWidth, Height);
            using (var brush = new SolidBrush(Color.GreenYellow))
            {
                e.Graphics.FillRectangle(brush, rect);
                e.Graphics.FillPolygon(brush, triangle);
            }
        }
    }
}
