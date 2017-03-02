namespace T3000Controls
{
    using System.ComponentModel;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Windows.Forms;

    public partial class IndicatorControl : UserControl
    {
        #region DesignerProperties

        private bool _isSimple = true;
        [Description("Simple version of indicator"), Category("Appearance")]
        public bool IsSimple
        {
            get { return _isSimple; }
            set
            {
                _isSimple = value;
                textLabel.Visible = !value;
                valueLabel.Visible = !value;

                Invalidate();
            }
        }

        [Description("Indicator text"), Category("Appearance")]
        public string IndicatorText
        {
            get { return textLabel.Text; }
            set { textLabel.Text = value; }
        }

        private float _value = 0.0F;
        [Description("Value for indicator"), Category("Appearance")]
        public float Value
        {
            get { return _value; }
            set {
                _value = value;
                valueLabel.Text = $"{_value.ToString("F1")}{AdditionalText}";
            }
        }

        private string _additionalText = " F";
        [Description("Additional text for value"), Category("Appearance")]
        public string AdditionalText
        {
            get { return _additionalText; }
            set
            {
                _additionalText = value;
                //Update value label text
                Value = Value;
            }
        }

        private Color _borderColor = Color.Black;
        [Description("Color for border"), Category("Appearance")]
        public Color BorderColor
        {
            get { return _borderColor; }
            set {
                _borderColor = value;

                Invalidate();
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
            if (IsSimple)
            {
                path.AddPolygon(new[] {
                    new PointF(0, 0),
                    new PointF(Width - 1, Height / 2.0F),
                    new PointF(0, Height - 1),
                });
            }
            else
            {
                path.AddPolygon(new[] {
                    new PointF(0, 0),
                    new PointF(Width - Height, 0),
                    new PointF(Width - 1, Height / 2.0F),
                    new PointF(Width - Height, Height - 1),
                    new PointF(0, Height - 1),
                });
            }

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
