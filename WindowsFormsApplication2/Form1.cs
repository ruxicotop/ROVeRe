using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using ExcelLibrary.Office.Excel;
using System.IO.Ports;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            serialPort1.BaudRate = 9600;
            serialPort1.PortName = "COM7";
            //label1.Text = "conectat";
         //   label2.Visible = true;
          //  label4.Visible = true;
          //  label6.Visible = true;
         //   label2.Text = serialPort1.ReadTo("!")+"*C";
          //  label4.Text = serialPort1.ReadTo("!")+"%";
          //  label6.Text = serialPort1.ReadTo("!");

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen) serialPort1.Open();
            label10.Text = "Conectat";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            label10.Text = "Deconectat";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string filename = "Test.xls";
            Workbook workbook = new Workbook();
            Worksheet sheet = new Worksheet("Test");
            workbook.Worksheets.Add(sheet);

            for (int i = 0; i < 100; i++)
                sheet.Cells[i, 0] = new Cell("");

            workbook.Save(filename);
        }
    }
}
