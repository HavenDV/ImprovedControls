namespace T3000Controls
{
    using System.ComponentModel;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Windows.Forms;

    public partial class IndicatorControl : UserControl
    {
        #region DesignerProperties

        [Description("Indicator text"), Category("Data")]
        public string IndicatorText
        {
            get { return textLabel.Text; }
            set { textLabel.Text = value; }
        }

        private float _value = 0.0F;
        [Description("Value for indicator"), Category("Data")]
        public float Value {
            get { return _value; }
            set {
                _value = value;
                valueLabel.Text = $"{_value.ToString("F1")} F";
            }
        }

        private Color _borderColor = Color.Black;
        [Description("Color for border"), Category("Appearance")]
        public Color BorderColor {
            get { return _borderColor; }
            set {
                _borderColor = value;

                if (DesignMode)
                {
                    Invalidate();
                }
            }
        }

        #endregion

        public IndicatorControl()
        {
            InitializeComponent();

            ResizeRedraw = true;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var graphics = e.Graphics;

            var path = new GraphicsPath();
            path.AddPolygon(new[] {
                new Point(0, 0),
                new Point(Width - Height, 0),
                new Point(Width, Height / 2),
                new Point(Width - Height, Height - 1),
                new Point(0, Height - 1),
            });

            using (var brush = new SolidBrush(BackColor))
            {
                graphics.FillPath(brush, path);
            }

            using (var pen = new Pen(BorderColor, 1))
            {
                graphics.DrawPath(pen, path);
            }

            Region = GraphicsUtilities.GetRegionForPath(path);
        }
    }
}
