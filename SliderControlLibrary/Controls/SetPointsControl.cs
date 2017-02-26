namespace T3000Controls
{
    using System.Windows.Forms;
    using System.Runtime.InteropServices;

    public partial class SetPointsControl : UserControl
    {
        private MouseMover Mover { get; set; }

        public SetPointsControl()
        {
            InitializeComponent();

            valueSlider.SliderName = "Temp";
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
            point.X = valueSlider.Location.X;

            valueSlider.SliderValue = $"{point.Y.ToString()}.5 F";
            valueSlider.Location = point;
        }

        [ComRegisterFunction()]
        public static void RegisterClass(string key) => ComUtilities.RegisterControlClass(key);

        [ComUnregisterFunction()]
        public static void UnregisterClass(string key) => ComUtilities.UnregisterControlClass(key);
    }
}
