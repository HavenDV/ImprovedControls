namespace T3000Controls
{
    using System.Reflection;
    using Microsoft.Win32;
    using System.Runtime.InteropServices;

    public static class ComUtilities
    {
        ///	<summary>
        ///	Register the class as a	control	and	set	it's CodeBase entry
        ///	</summary>
        ///	<param name="key">The registry key of the control</param>
        public static void RegisterControlClass(string key)
        {
            // Strip off HKEY_CLASSES_ROOT\ from the passed key as I don't need it
            key = key.Replace(@"HKEY_CLASSES_ROOT\", "");

            // Open the CLSID\{guid} key for write access
            using (var k = Registry.ClassesRoot.OpenSubKey(key, true))
            {
                // And create	the	'Control' key -	this allows	it to show up in
                // the ActiveX control container
                using (k?.CreateSubKey("Control")) { }
                using (var server = k?.OpenSubKey("InprocServer32", true))
                {
                    // Next create the CodeBase entry	- needed if	not	string named and GACced.
                    server?.SetValue("CodeBase", Assembly.GetExecutingAssembly().CodeBase);
                }
            }
        }

        ///	<summary>
        ///	Called to unregister the control
        ///	</summary>
        ///	<param name="key">Tke registry key</param>
        [ComUnregisterFunction()]
        public static void UnregisterControlClass(string key)
        {
            key = key.Replace(@"HKEY_CLASSES_ROOT\", "");

            // Open	HKCR\CLSID\{guid} for write	access
            using (var k = Registry.ClassesRoot.OpenSubKey(key, true))
            {
                // Delete the 'Control'	key, but don't throw an	exception if it	does not exist
                k?.DeleteSubKey("Control", false);

                // Next	open up	InprocServer32
                using (var server = k?.OpenSubKey("InprocServer32", true))
                {
                    // And delete the CodeBase key,	again not throwing if missing
                    server?.DeleteValue("CodeBase", false);
                }
            }
        }
    }
}
