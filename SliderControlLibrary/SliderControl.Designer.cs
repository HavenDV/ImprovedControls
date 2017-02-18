namespace T3000Controls
{
    partial class SliderControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.heatingHandle = new T3000Controls.HandleControl();
            this.coolingHandle = new T3000Controls.HandleControl();
            this.SuspendLayout();
            // 
            // heatingHandle
            // 
            this.heatingHandle.BackColor = System.Drawing.Color.Transparent;
            this.heatingHandle.BorderColor = System.Drawing.Color.White;
            this.heatingHandle.Location = new System.Drawing.Point(0, 129);
            this.heatingHandle.Name = "heatingHandle";
            this.heatingHandle.Size = new System.Drawing.Size(98, 17);
            this.heatingHandle.SliderColor = System.Drawing.Color.Red;
            this.heatingHandle.SliderValue = "Value";
            this.heatingHandle.TabIndex = 1;
            // 
            // coolingHandle
            // 
            this.coolingHandle.BackColor = System.Drawing.Color.Transparent;
            this.coolingHandle.BorderColor = System.Drawing.Color.White;
            this.coolingHandle.Location = new System.Drawing.Point(0, 44);
            this.coolingHandle.Name = "coolingHandle";
            this.coolingHandle.Size = new System.Drawing.Size(98, 16);
            this.coolingHandle.SliderColor = System.Drawing.Color.DeepSkyBlue;
            this.coolingHandle.SliderValue = "75.5F";
            this.coolingHandle.TabIndex = 0;
            // 
            // Panel
            // 
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.heatingHandle);
            this.Controls.Add(this.coolingHandle);
            this.DoubleBuffered = true;
            this.Name = "Panel";
            this.Size = new System.Drawing.Size(163, 195);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Panel_Paint);
            this.ResumeLayout(false);

        }

        #endregion

        private HandleControl coolingHandle;
        private HandleControl heatingHandle;
    }
}
