namespace T3000Controls
{
    using System.ComponentModel;
    using System.Drawing;
    using System.Windows.Forms;

    public partial class BackgroundControl : UserControl
    {
        #region DesignerProperties

        [Description("Color for lines"), Category("Appearance")]
        public Color LinesColor { get; set; } = Color.DarkGray;

        [Description("Color for borders"), Category("Appearance")]
        public Color BorderColor { get; set; } = Color.Black;

        [Description("Color for cooling"), Category("Appearance")]
        public Color TopZoneColor { get; set; } = Color.DeepSkyBlue;

        [Description("Color for heating"), Category("Appearance")]
        public Color BottomZoneColor { get; set; } = Color.Red;

        [Description("Top zone"), Category("Data")]
        public bool TopZone { get; set; } = true;

        [Description("Bottom zone"), Category("Data")]
        public bool BottomZone { get; set; } = true;

        [Description("Current value Y"), Category("Data")]
        public float CurrentValueY { get; set; } = 50;

        [Description("Top zone value Y"), Category("Data")]
        public float TopZoneValueY { get; set; } = 66;

        [Description("Bottom zone value Y"), Category("Data")]
        public float BottomZoneValueY { get; set; } = 33;

        [Description("Step height"), Category("Data")]
        public float StepHeight { get; set; } = 10;

        [Description("Small offset Y"), Category("Data")]
        public float SmallOffsetY { get; set; } = 5;

        [Description("Big offset Y"), Category("Data")]
        public float BigOffsetY { get; set; } = 10;

        #endregion

        public BackgroundControl()
        {
            InitializeComponent();

            ResizeRedraw = true;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var graphics = e.Graphics;

            graphics.Clear(BackColor);

            var x1 = 0;
            var x2 = Width - 1;
            if (TopZone)
            {
                using (var brush = new SolidBrush(TopZoneColor))
                {
                    var rect = new RectangleF(x1, 0, x2, TopZoneValueY);
                    graphics.FillRectangle(brush, rect);
                }
            }
            if (BottomZone)
            {
                using (var brush = new SolidBrush(BottomZoneColor))
                {
                    var rect = RectangleF.FromLTRB(x1, BottomZoneValueY, x2, Height - 1);
                    graphics.FillRectangle(brush, rect);
                }
            }

            using (var pen = new Pen(LinesColor))
            {
                for (var height = SmallOffsetY; height < Height; height += StepHeight)
                {
                    graphics.DrawLine(pen, 0.2F * x2, height, 0.8F * x2, height);
                }
            }

            using (var pen = new Pen(LinesColor, 2))
            {
                for (var height = BigOffsetY; height < Height; height += StepHeight)
                {
                    graphics.DrawLine(pen, 0.1F * x2, height, 0.9F * x2, height);
                }
            }

            using (var pen = new Pen(BorderColor))
            {
                graphics.DrawLine(pen, 0, CurrentValueY, Width - 1, CurrentValueY);
                graphics.DrawRectangle(pen, x1, 0, x2, Height - 1);
            }
        }
    }
}
