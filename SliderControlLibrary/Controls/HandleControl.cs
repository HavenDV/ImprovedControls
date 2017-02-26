using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace T3000Controls
{
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
                valueLabel.Text = $"{_value.ToString("F1")} F";
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

                if (DesignMode)
                {
                    Invalidate();
                }
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

            var graphics = e.Graphics;

            var polygonWidth = Height;
            var smallRadius = 3;
            var smallWidth = 50;
            var textRadius = 10;
            var polygon = new Point[] {
                new Point(0, Height / 2),
                new Point(smallRadius, Height / 2 - smallRadius),
                new Point(smallWidth, Height / 2 - smallRadius),
                new Point(smallWidth + textRadius, 0),
                new Point(Width - textRadius - 1, 0),
                new Point(Width - 1, Height / 2 - smallRadius),
                new Point(Width - 1, Height / 2 + smallRadius - 1),
                new Point(Width - textRadius - 1, Height - 1 - 1),
                new Point(smallWidth + textRadius, Height - 1 - 1),
                new Point(smallWidth, Height / 2 + smallRadius - 1),
                new Point(smallRadius, Height / 2 + smallRadius - 1)
            };

            using (var brush = new SolidBrush(BackColor))
            {
                graphics.FillPolygon(brush, polygon);
            }

            using (var pen = new Pen(BorderColor, 1))
            {
                graphics.DrawPolygon(pen, polygon);
            }

            for (var i = 6; i < polygon.Length; ++i)
            {
                polygon[i].Y += 1;
            }
            for (var i = 4; i < 8; ++i)
            {
                polygon[i].X += 1;
            }

            var path = new GraphicsPath();
            path.AddPolygon(polygon);
            Region = new Region(path);
        }
    }
}
