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
            this.slider1 = new Slider();
            this.SuspendLayout();
            // 
            // slider1
            // 
            this.slider1.BackColor = System.Drawing.Color.Transparent;
            this.slider1.Location = new System.Drawing.Point(22, 157);
            this.slider1.Name = "slider1";
            this.slider1.Size = new System.Drawing.Size(101, 28);
            this.slider1.TabIndex = 1;
            this.slider1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseDown);
            this.slider1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseMove);
            this.slider1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.slider1_MouseUp);
            // 
            // SliderControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Maroon;
            this.Controls.Add(this.slider1);
            this.Name = "SliderControl";
            this.Size = new System.Drawing.Size(432, 359);
            this.ResumeLayout(false);

        }

        #endregion

        private Slider slider1;
    }
}
