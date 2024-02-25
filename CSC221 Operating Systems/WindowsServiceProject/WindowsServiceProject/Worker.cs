namespace App.WindowsService;
using Microsoft.Extensions.Logging;
using WindowsServiceProject;

// these libs for sending email
using MailKit.Net.Smtp;
using MimeKit; 
using System.Text;

public sealed class WindowsBackgroundService(
ILogger<WindowsBackgroundService> logger) : BackgroundService
{
	//Important information about sending the email
	//And I won't leave my acutal info here
	private string SENDER_EMAIL = "Sender email here";
	private string RECIPENT_EMAIL = "Recipent email here";
	private string SMTP_HOST = "smtp.gmail.com"; //Your smtp host
	private string USER_NAME = "Username for the smtp host";
	private string USER_PASSWORD = "Password for the smtp host";
	private int HOUR_INTERVAL = 1; 

	private int PORT = 465;

	[System.Runtime.Versioning.SupportedOSPlatform("windows")] //To remove the warning that says it might be run on other OSes
	protected override async Task ExecuteAsync(CancellationToken stoppingToken)
	{
		collectInformation collectInformation = new(); //check this class to know how getting the workload works
		try
		{
			while (!stoppingToken.IsCancellationRequested)
			{
				string cpuInformation = collectInformation.cpuInformation();

				string memInformation = collectInformation.memoryInformation();

				string storageInfo = collectInformation.storageInformation();

				string networkInfo = collectInformation.networkInformation();


				string allInformation = "--------------\n" + cpuInformation + "\n--------------\n" + memInformation + "\n--------------\n" + storageInfo + "\n--------------\n" + networkInfo + "\n--------------\n";


				//Creating and saving the txt file at desktop
				string fileName = DateTime.Now.ToString("dd-MM-yyy") + "report.txt";
				fileName = fileName.Replace(" ", "");
				string desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
				string fullFilePath = Path.Combine(desktopPath, fileName);
				try
				{
					if (File.Exists(fullFilePath))
					{
						File.Delete(fullFilePath);
					}

					using (FileStream fs = File.Create(fullFilePath))
					{
						Byte[] text = new UTF8Encoding(true).GetBytes(allInformation);
						fs.Write(text, 0, text.Length);
						byte[] author = new UTF8Encoding(true).GetBytes("WorkLoad information windows service");
						fs.Write(author, 0, author.Length);
					}

					await Console.Out.WriteLineAsync("Report generated");
					//Send the email in this method
					sendEmail(RECIPENT_EMAIL, fullFilePath);
					await Console.Out.WriteLineAsync("Email sent");

					//delete the file after finishing
					File.Delete(fullFilePath);
				}
				catch (Exception e)
				{
					await Console.Out.WriteLineAsync(e.ToString());
				}

				await Task.Delay(TimeSpan.FromHours(HOUR_INTERVAL), stoppingToken);
			}
		}
		catch (OperationCanceledException)
		{
			// When the stopping token is canceled, for example, a call made from services.msc,
			// we shouldn't exit with a non-zero exit code. In other words, this is expected...
		}
		catch (Exception ex)
		{
			logger.LogError(ex, "{Message}", ex.Message);
			Environment.Exit(1);
		}
	}



	private void sendEmail(string recipentEmail, string attachemntPath)
	{
		string currentTime = DateTime.Now.ToString("F");
		var message = new MimeMessage();
		message.From.Add(new MailboxAddress(name:"Work Load Information", address: SENDER_EMAIL));
		message.To.Add(new MailboxAddress(name:"Recipent", address: recipentEmail));
		message.Subject = "Snapshot of your pc workload at " + currentTime;

		//Building the email
		BodyBuilder builder = new BodyBuilder();
		//creating the text of the email
		builder.TextBody = "Snapshot of your pc workload at " + currentTime;
		//adding the txt file
		builder.Attachments.Add(attachemntPath);
		//combining and creating the messagebody
		message.Body = builder.ToMessageBody();

		//sending the acual email
		using(SmtpClient client = new())
		{
			client.Connect(host: SMTP_HOST, port: PORT, useSsl: true);
			client.Authenticate(userName: USER_NAME, password: USER_PASSWORD);
			client.Send(message);
			client.Disconnect(quit:true);
		}

		

	}


}


