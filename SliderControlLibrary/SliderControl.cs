using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class SliderControl : UserControl
    {
        public SliderControl()
        {
            InitializeComponent();
        }

        private void Panel_Paint(object sender, PaintEventArgs e)
        {
            var x1 = 0;
            var x2 = 0.5F * Width;
            using (var brush = new SolidBrush(Color.DeepSkyBlue))
            {
                var rect = new RectangleF(x1, 0, x2, 0.33F * Height);
                e.Graphics.FillRectangle(brush, rect);
            }
            using (var brush = new SolidBrush(Color.GreenYellow))
            {
                var rect = new RectangleF(x1, 0.33F * Height, x2, 0.33F * Height);
                e.Graphics.FillRectangle(brush, rect);
            }
            using (var brush = new SolidBrush(Color.Red))
            {
                var rect = new RectangleF(x1, 0.66F * Height, x2, 0.34F * Height);
                e.Graphics.FillRectangle(brush, rect);
            }

            using (var pen = new Pen(Color.DarkGray))
            {
                for (var i = 0; i < 20; ++i)
                {
                    var height = 0.05F*i*Height;
                    e.Graphics.DrawLine(pen, 0.2F * x2, height, 0.8F * x2, height);
                }
            }

            using (var pen = new Pen(Color.DarkGray, 2))
            {
                for (var i = 0; i < 20; ++i)
                {
                    var height = 0.05F * i * Height + 0.025F * Height;
                    e.Graphics.DrawLine(pen, 0.1F * x2, height, 0.9F * x2, height);
                }
            }

            using (var pen = new Pen(Color.Black))
            {
                var height = 0.5F * Height;
                e.Graphics.DrawLine(pen, 0, height, Width, height);
                e.Graphics.DrawRectangle(pen, x1, 0, x2 - 1, Height - 1);
            }
        }
    }
}
