namespace T3000Controls
{
    using System.Drawing;
    using System.Windows.Forms;

    using System.Runtime.InteropServices;
    using System.Reflection;
    using Microsoft.Win32;

    [ProgId("T3000Controls.SliderControl")]
    public partial class SetPointsControl: UserControl
    {
        private MouseMover Mover { get; set; }

        public SetPointsControl()
        {
            InitializeComponent();

            valueSlider.SliderName = "Temp";
            Mover = new MouseMover(this);
        }

        private void slider1_MouseDown(object sender, MouseEventArgs args)
        {
            Mover.Start(args.Location, valueSlider);
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

            var point = PointToClient(valueSlider.PointToScreen(e.Location));
            point.Offset(Mover.Offset);

            //Save X coordinate from slider
            point.X = valueSlider.Location.X;

            valueSlider.SliderValue = $"{point.Y.ToString()}.5 F";

            valueSlider.Location = point;
        }

        ///	<summary>
        ///	Register the class as a	control	and	set	it's CodeBase entry
        ///	</summary>
        ///	<param name="key">The registry key of the control</param>
        [ComRegisterFunction()]
        public static void RegisterClass(string key)
        {
            // Strip off HKEY_CLASSES_ROOT\ from the passed key as I don't need it
            key = key.Replace(@"HKEY_CLASSES_ROOT\", "");

            // Open the CLSID\{guid} key for write access
            var k = Registry.ClassesRoot.OpenSubKey(key, true);

            // And create	the	'Control' key -	this allows	it to show up in
            // the ActiveX control container
            var ctrl = k.CreateSubKey("Control");
            ctrl.Close();

            // Next create the CodeBase entry	- needed if	not	string named and GACced.
            var inprocServer32 = k.OpenSubKey("InprocServer32", true);
            inprocServer32.SetValue("CodeBase", Assembly.GetExecutingAssembly().CodeBase);
            inprocServer32.Close();

            // Finally close the main	key
            k.Close();
        }

        ///	<summary>
        ///	Called to unregister the control
        ///	</summary>
        ///	<param name="key">Tke registry key</param>
        [ComUnregisterFunction()]
        public static void UnregisterClass(string key)
        {
            key = key.Replace(@"HKEY_CLASSES_ROOT\", "");

            // Open	HKCR\CLSID\{guid} for write	access
            var k = Registry.ClassesRoot.OpenSubKey(key, true);

            // Delete the 'Control'	key, but don't throw an	exception if it	does not exist
            k.DeleteSubKey("Control", false);

            // Next	open up	InprocServer32
            var inprocServer32 = k.OpenSubKey("InprocServer32", true);

            // And delete the CodeBase key,	again not throwing if missing
            k.DeleteSubKey("CodeBase", false);

            // Finally close the main key
            k.Close();
        }
    }
}
