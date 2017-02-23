using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

namespace T3000Controls
{
    public partial class BackgroundControl : UserControl
    {
        [Description("Color for lines"), Category("Appearance")]
        public Color LinesColor { get; set; } = Color.DarkGray;

        [Description("Color for borders"), Category("Appearance")]
        public Color BorderColor { get; set; } = Color.Black;

        [Description("Top value"), Category("Data")]
        public float TopValue { get; set; } = 100;

        [Description("Bottom value"), Category("Data")]
        public float BottomValue { get; set; } = 0;

        [Description("Current value"), Category("Data")]
        public float CurrentValue { get; set; } = 50;

        [Description("Top zone"), Category("Data")]
        public bool TopZone { get; set; } = true;

        [Description("Top zone value"), Category("Data")]
        public float TopZoneValue { get; set; } = 66;

        [Description("Color for cooling"), Category("Appearance")]
        public Color TopZoneColor { get; set; } = Color.DeepSkyBlue;

        [Description("Bottom zone"), Category("Data")]
        public bool BottomZone { get; set; } = true;

        [Description("Bottom zone value"), Category("Data")]
        public float BottomZoneValue { get; set; } = 33;

        [Description("Color for heating"), Category("Appearance")]
        public Color BottomZoneColor { get; set; } = Color.Red;

        public BackgroundControl()
        {
            InitializeComponent();
        }

        public float YToValue(int y)
        {
            var delta = Math.Abs(TopValue - BottomValue);
            var oneValue = delta / Height;
            var value = y*oneValue;
            return TopValue > BottomValue ? TopValue - value : TopValue + value;
        }

        public int ValueToY(float value)
        {
            var delta = Math.Abs(TopValue - BottomValue);
            var oneValueHeight = Height / delta;
            return (int)Math.Round(value * oneValueHeight);
        }

        public void UpdateHandlePosition(HandleControl handle)
        {
            var point = handle.Location;
            point.Y = ValueToY(handle.Value) - handle.Height / 2;
            handle.Location = point;
        }

        protected override void OnPaint(PaintEventArgs args)
        {
            args.Graphics.Clear(BackColor);

            var x1 = 0;
            var x2 = Width - 1;
            using (var brush = new SolidBrush(TopZoneColor))
            {
                var rect = new RectangleF(x1, 0, x2, ValueToY(TopZoneValue));
                args.Graphics.FillRectangle(brush, rect);
            }
            using (var brush = new SolidBrush(BottomZoneColor))
            {
                var rect = new RectangleF(x1, ValueToY(BottomZoneValue), x2, Height - ValueToY(BottomZoneValue));
                args.Graphics.FillRectangle(brush, rect);
            }

            using (var pen = new Pen(LinesColor))
            {
                var diff = Math.Abs(TopValue / 5 - TopValue / 5.0F) * 5;
                var offset = TopValue < BottomValue ? 5 - diff : diff;
                for (var height = ValueToY(offset); height < Height; height += ValueToY(10))
                {
                    args.Graphics.DrawLine(pen, 0.2F * x2, height, 0.8F * x2, height);
                }
            }

            using (var pen = new Pen(LinesColor, 2))
            {
                var diff = Math.Abs(TopValue/10 - TopValue/10.0F)*10;
                var offset = TopValue < BottomValue ? 10 - diff : diff;
                for (var height = ValueToY(offset); height < Height; height += ValueToY(10))
                {
                    args.Graphics.DrawLine(pen, 0.1F * x2, height, 0.9F * x2, height);
                }
            }

            using (var pen = new Pen(BorderColor))
            {
                var height = ValueToY(CurrentValue);
                args.Graphics.DrawLine(pen, 0, height, Width, height);
                args.Graphics.DrawRectangle(pen, x1, 0, x2, Height - 1);
            }
        }
    }
}
