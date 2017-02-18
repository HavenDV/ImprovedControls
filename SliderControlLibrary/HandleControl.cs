using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class HandleControl : UserControl
    {
        [Description("Value for slider"), Category("Appearance")]
        public string SliderValue {
            get { return valueLabel.Text; }
            set { valueLabel.Text = value; }
        }

        [Description("Color for slider"), Category("Appearance")]
        public Color SliderColor { get; set; } = Color.White;

        [Description("Color for border"), Category("Appearance")]
        public Color BorderColor { get; set; } = Color.White;

        public HandleControl()
        {
            InitializeComponent();

            SetStyle(ControlStyles.ResizeRedraw, true);
        }

        protected override void OnPaint(PaintEventArgs args)
        {
            base.OnPaint(args);

            var polygonWidth = Height;
            var smallRadius = 3;
            var smallWidth = 50;
            var textRadius = 10;
            var polygon = new Point[] {
                new Point(0, Height / 2),
                new Point(smallRadius, Height / 2 - smallRadius),
                new Point(smallWidth, Height / 2 - smallRadius),
                new Point(smallWidth + textRadius, 0),
                new Point(Width - textRadius, 0),
                new Point(Width, Height / 2 - smallRadius),
                new Point(Width, Height / 2 + smallRadius),
                new Point(Width - textRadius, Height - 1),
                new Point(smallWidth + textRadius, Height - 1),
                new Point(smallWidth, Height / 2 + smallRadius),
                new Point(smallRadius, Height / 2 + smallRadius)
            };

            using (var brush = new SolidBrush(SliderColor))
            {
                args.Graphics.FillPolygon(brush, polygon);
            }

            using (var pen = new Pen(BorderColor, 1))
            {
                args.Graphics.DrawPolygon(pen, polygon);
            }

            var path = new GraphicsPath();
            path.AddPolygon(polygon);
            //Region = new Region(path);
        }
    }
}
