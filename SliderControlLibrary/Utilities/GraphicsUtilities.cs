namespace T3000Controls
{
    using System.Drawing;
    using System.Drawing.Drawing2D;

    public static class GraphicsUtilities
    {
        public static GraphicsPath CreateRoundedRectanglePath(Rectangle rect, int radius)
        {
            var path = new GraphicsPath();
            path.AddArc(rect.X, rect.Y, radius, radius, 180, 90);
            path.AddArc(rect.X + rect.Width - radius - 1, rect.Y, radius, radius, 270, 90);
            path.AddArc(rect.X + rect.Width - radius - 1, rect.Y + rect.Height - radius - 1, radius, radius, 0, 90);
            path.AddArc(rect.X, rect.Y + rect.Height - radius - 1, radius, radius, 90, 90);
            path.CloseAllFigures();

            return path;
        }

        public static Region GetRegionForPath(GraphicsPath path)
        {
            var region = new Region(path);
            path.Widen(SystemPens.ActiveBorder);
            region.Union(path);

            return region;
        }
    }
}