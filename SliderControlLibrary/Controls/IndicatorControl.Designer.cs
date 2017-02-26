namespace T3000Controls
{
    partial class IndicatorControl
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
            this.textLabel = new T3000Controls.TransparentLabel();
            this.valueLabel = new T3000Controls.TransparentLabel();
            this.SuspendLayout();
            // 
            // textLabel
            // 
            this.textLabel.AutoSize = true;
            this.textLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textLabel.Location = new System.Drawing.Point(3, 17);
            this.textLabel.Name = "textLabel";
            this.textLabel.Size = new System.Drawing.Size(39, 20);
            this.textLabel.TabIndex = 0;
            this.textLabel.Text = "Text";
            // 
            // valueLabel
            // 
            this.valueLabel.AutoSize = true;
            this.valueLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.valueLabel.Location = new System.Drawing.Point(60, 14);
            this.valueLabel.Name = "valueLabel";
            this.valueLabel.Size = new System.Drawing.Size(64, 24);
            this.valueLabel.TabIndex = 1;
            this.valueLabel.Text = "Value";
            // 
            // IndicatorControl
            // 
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.valueLabel);
            this.Controls.Add(this.textLabel);
            this.DoubleBuffered = true;
            this.Name = "IndicatorControl";
            this.Size = new System.Drawing.Size(132, 49);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TransparentLabel textLabel;
        private TransparentLabel valueLabel;
    }
}
