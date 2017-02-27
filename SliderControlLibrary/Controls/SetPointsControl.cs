namespace T3000Controls
{
    using System.Windows.Forms;
    using System.Runtime.InteropServices;
    using System;

    public partial class SetPointsControl : UserControl
    {
        public SetPointsControl()
        {
            InitializeComponent();

            ResizeRedraw = true;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var point = indicator.Location;
            point.Y = Convert.ToInt32(panel.ValueToY(panel.CurrentValue) - indicator.Height / 2.0F) + panel.Location.Y;

            indicator.Location = point;
            indicator.Value = panel.CurrentValue;
            indicator.Refresh();
        }

        [ComRegisterFunction()]
        public static void RegisterClass(string key) => ComUtilities.RegisterControlClass(key);

        [ComUnregisterFunction()]
        public static void UnregisterClass(string key) => ComUtilities.UnregisterControlClass(key);
    }
}
