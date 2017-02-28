namespace T3000Controls
{
    using System.ComponentModel;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Windows.Forms;

    public partial class SmallIndicatorControl : UserControl
    {
        #region DesignerProperties

        [Description("Value for indicator"), Category("Data")]
        public float Value { get; set; }

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

        public SmallIndicatorControl()
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
                new PointF(0, 0),
                new PointF(Width - 1, Height / 2.0F),
                new PointF(0, Height - 1),
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
