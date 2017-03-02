namespace T3000Controls
{
    using System.ComponentModel;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Windows.Forms;

    public partial class HandleControl : UserControl
    {
        #region DesignerProperties

        private float _value = 0.0F;
        [Description("Value for handle"), Category("Data")]
        public float Value
        {
            get { return _value; }
            set
            {
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
                Invalidate();
            }
        }

        private int _handleWidth = 50;
        [Description("Handle width"), Category("Appearance")]
        public int HandleWidth
        {
            get { return _handleWidth; }
            set
            {
                _handleWidth = value;
                Invalidate();
            }
        }

        private int _handleHeight = 10;
        [Description("Handle height"), Category("Appearance")]
        public int HandleHeight
        {
            get { return _handleHeight; }
            set
            {
                _handleHeight = value;
                Invalidate();
            }
        }

        private Color _borderColor = Color.White;
        [Description("Color for border"), Category("Appearance")]
        public Color BorderColor
        {
            get { return _borderColor; }
            set
            {
                _borderColor = value;
                Invalidate();
            }
        }

        #endregion

        public HandleControl()
        {
            InitializeComponent();

            ResizeRedraw = true;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            valueLabel.Location = new Point(HandleWidth, 1);
            valueLabel.Size = new Size(Width - HandleWidth, Height - 3);

            var handleRectangle = new Rectangle(0, Height / 2 - HandleHeight / 2 - 1, HandleWidth, HandleHeight);
            var textRectangle = new Rectangle(HandleWidth, 0, Width - HandleWidth - 2, Height - 2);
            var handlePath = GraphicsUtilities.CreateRoundedRectanglePath(handleRectangle, 4);
            var textPath = GraphicsUtilities.CreateRoundedRectanglePath(textRectangle, 8);

            var graphics = e.Graphics;

            using (var brush = new SolidBrush(BackColor))
            {
                graphics.FillPath(brush, handlePath);
                graphics.FillPath(brush, textPath);
            }
            using (var pen = new Pen(BorderColor))
            {
                pen.StartCap = LineCap.Round;
                pen.EndCap = LineCap.Round;
                graphics.DrawPath(pen, handlePath);
                graphics.DrawPath(pen, textPath);
            }
            using (var brush = new SolidBrush(BackColor))
            {
                var rect = handleRectangle;
                rect.Inflate(2, -1);
                graphics.FillRectangle(brush, rect);
            }

            var region = GraphicsUtilities.GetRegionForPath(handlePath);
            region.Union(GraphicsUtilities.GetRegionForPath(textPath));
            Region = region;
        }
    }
}
