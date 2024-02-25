using System;
using System.Collections.Generic;
using System.Diagnostics; // get access to alot of usefull things in monitoring
using System.Linq;
using System.Management; // used to get total memory size
using System.Threading.Tasks;




namespace WindowsServiceProject
{
	[System.Runtime.Versioning.SupportedOSPlatform("windows")] //To remove the warning that says it might be run on other OSes
	public class collectInformation
	{
		//initalizing the performance counters
		PerformanceCounter _cpuCounter = new();
		PerformanceCounter _memoryCounter = new();
		PerformanceCounter _diskWUsage = new();
		PerformanceCounter _diskRUsage = new();



		private double getCounterUsage(PerformanceCounter _counter, string categoryName, string counterName, string counterInstanceName)
		{

			_counter.CategoryName = categoryName;
			_counter.CounterName = counterName;
			_counter.InstanceName = counterInstanceName;
			return _counter.NextValue();

		}

		private double getCounterDelayedUsage(PerformanceCounter _counter, string categoryName, string counterName, string counterInstanceName)
		{

			_counter.CategoryName = categoryName;
			_counter.CounterName = counterName;
			_counter.InstanceName = counterInstanceName;
			_counter.NextValue();
			Thread.Sleep(1000);
			return _counter.NextValue();

		}

		//All these methods are the real implementaion
		private double getMemorySizeinGB()
		{
			ulong TotalPhysicalMemoryInBytes = 0;


			ManagementScope scope = new ManagementScope("\\\\.\\ROOT\\CIMV2");
			ObjectQuery query = new ObjectQuery("SELECT TotalPhysicalMemory FROM Win32_ComputerSystem");


			using (ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope, query))
			{
				foreach (ManagementObject queryObj in searcher.Get())
				{

					TotalPhysicalMemoryInBytes = Convert.ToUInt64(queryObj["TotalPhysicalMemory"]);
				}
			}


			return Math.Round(TotalPhysicalMemoryInBytes / Math.Pow(1024, 3), 2);
		}

		private double getUsedMemory()
		{
			double totalRamSize = getMemorySizeinGB();
			double freeRamInMBytes = getCounterUsage(_memoryCounter, "Memory", "Available MBytes", null);
			double freeRamInGBytes = Math.Round(freeRamInMBytes / 1024, 2);
			double usedRam = totalRamSize - freeRamInGBytes;
			return Math.Round((usedRam / totalRamSize) * 100, 2);

		}

		private string getStorageInfo()
		{
			DriveInfo[] drives = DriveInfo.GetDrives();
			string final = "";
			foreach (DriveInfo drive in drives)
			{
				string driveName = drive.Name.Replace(@"\", "");

				double driveWrite = Math.Round(getCounterDelayedUsage(_diskWUsage, "LogicalDisk", "Disk Write Bytes/sec", driveName), 2);
				double driveRead = Math.Round(getCounterDelayedUsage(_diskRUsage, "LogicalDisk", "Disk Read Bytes/sec", driveName), 2);
				final += $"{driveName} Disk Write Bytes/sec = {driveWrite} Bytes/sec\n{driveName} Disk Read Bytes/sec = {driveRead} Bytes/sec\n";
			}

			return final;
		}

		private string getNetworkInfo()
		{

			PerformanceCounterCategory performanceCounterCategory = new PerformanceCounterCategory("Network Interface");
			string instance = performanceCounterCategory.GetInstanceNames()[0]; // 1st NIC !
			PerformanceCounter performanceCounterSent = new PerformanceCounter("Network Interface", "Bytes Sent/sec", instance);
			PerformanceCounter performanceCounterReceived = new PerformanceCounter("Network Interface", "Bytes Received/sec", instance);

			performanceCounterSent.NextValue();
			performanceCounterReceived.NextValue();
			Thread.Sleep(1000);
			double byteSent = performanceCounterSent.NextValue();
			double byteReceived = performanceCounterReceived.NextValue();

			string final = $"Network bytes sent: {Math.Round(byteSent / 1024, 2)} KBytes\nNetwork bytes received: {Math.Round(byteReceived / 1024, 2)} KBytes";
			return final;

		}



		//these are just the public ones
		public string cpuInformation()
		{
			string final = "Current Processor usage = " + getCounterUsage(_cpuCounter,
																"Processor Information", "% Processor Utility", "_Total") + "%";
			return final;
		}

		public string memoryInformation()
		{
			string final = "Curret Memory usage = " + getUsedMemory() + "%";
			return final;
		}

		public string storageInformation()
		{
			return getStorageInfo();
		}

		public string ramInformation()
		{
			return getStorageInfo(); 
		}

		public string networkInformation()
		{
			string final = getNetworkInfo();
			return final;
		}
	}


	

}
