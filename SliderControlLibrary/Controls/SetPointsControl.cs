namespace T3000Controls
{
    using System.Windows.Forms;
    using System.Runtime.InteropServices;

    public partial class SetPointsControl : UserControl
    {
        private MouseMover Mover { get; }

        public SetPointsControl()
        {
            InitializeComponent();
            
            Mover = new MouseMover(this);
        }

        private void slider1_MouseDown(object sender, MouseEventArgs e)
        {
            Mover.Start(sender, e);
        }

        private void slider1_MouseUp(object sender, MouseEventArgs e)
        {
            Mover.End();
        }

        private void slider1_MouseMove(object sender, MouseEventArgs e)
        {
            if (!Mover.IsMoved)
            {
                return;
            }

            var point = Mover.GetPoint(e);

            //Save X coordinate from slider
            point.X = indicator.Location.X;

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
