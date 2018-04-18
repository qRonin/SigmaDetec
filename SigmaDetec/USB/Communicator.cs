﻿using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SigmaDetec.USB
{
    class Communicator
    {
        SerialPort _serialPort;
        public Communicator()
        {
            _serialPort = new SerialPort();
            _serialPort.PortName = "COM4"; 
            _serialPort.Open();
        }

        public void test()
        {
            Console.WriteLine("Available Ports:");
            foreach (string s in SerialPort.GetPortNames())
            {
                Console.WriteLine("   {0}", s);
            }
            new Task(() =>
            {
                _serialPort.WriteLine("sdfsdf");
            }).Start();
        }
    }
}