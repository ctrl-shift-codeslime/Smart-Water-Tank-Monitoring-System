# Smart-Water-Tank-Monitoring-System

This is a small helper function called isValid that acts like a gatekeeper for our inputs. It takes the water level entered by the user and checks if it falls between 0 and 100 percent. If the number is valid, it sends back a 1 (meaning true) so the program can continue; if the number is negative or over 100, it sends back a 0 (meaning false), which tells the main function to ask the user to try again.

• int isValid(...): The int at the start means this function will hand back a whole number—specifically 1 for yes/true, or 0 for no/false.

• (float level): This is the input the function receives—a decimal number (float) representing the tank's water percentage.

• level >= 0 && level <= 100: The && means AND. Both rules must be true at the same time: the level must be at least 0 and no more than 100.

• return (...): Instead of writing a long if-else block, C automatically evaluates that comparison to 1 (if true) or 0 (if false) and sends that answer right back to main().

This helper function, showRecommendation, takes a tank's water percentage and prints out the exact advice for the user. First, it neatly displays the water level rounded to two decimal places. Then, it uses an if - else if - else decision chain to check which zone the water falls into: if it's below 25%, it advises starting the pump; if it's between 25% and 90%, it says to keep monitoring; and if it's 90% or higher, it tells the user to stop the pump so the tank doesn't overflow.

• void showRecommendation(float level): void means this function just prints text to the screen and doesn't send any value back to main(), while (float level) is the tank's water percentage passed into it.

• %.2f%%: %.2f formats the decimal number to show exactly two digits after the decimal point (like 45.50), and %% is how C prints a single literal % sign on the screen.

• if (level < 25): Catches critically low tanks (0% up to 24.99%) and recommends turning on the pump.

• else if (level < 90): Since the first if already ruled out anything under 25%, this automatically covers the safe middle range (25% up to 89.99%).

• else: Catches everything else (90% to 100%) and warns the user to shut off the pump.

This is the first half of the main() function, where the program sets up its memory and collects valid data from the user. First, it declares an array to hold up to 10 tank readings, along with counters and a file pointer, and prints the welcome banner. Then, it enters a do loop that resets the low-tank counter (fillCount) to zero for a fresh check. It asks how many tanks to monitor—using a while loop to reject any number outside 1 to 10—and then uses a for loop to collect each tank's water level, calling our isValid function to catch bad inputs and counting how many tanks are running low below 25%.

• Variable Setup (float levels[10], int n, i, fillCount, char choice, FILE *fp): Creates a list (levels[10]) capable of storing 10 decimal readings, integers for the tank count (n), loop index (i), and low-tank counter (fillCount), a character (choice) for repeating the program, and a pointer (fp) for saving the report file.

• do { fillCount = 0; ... }: Starts the main repeating cycle and resets fillCount to 0 at the beginning of every run so old counts don't carry over.

• while (n < 1 || n > 10): An input trap—if the user enters 0, a negative number, or more than 10 tanks, this loop keeps asking until they enter a valid count (|| means OR).

• for (i = 0; i < n; i++): Steps through each tank one by one (starting at index 0 in memory, while displaying i + 1 so the user sees Tank 1, Tank 2, etc.).

• while (!isValid(levels[i])): The ! means NOT. As long as isValid() says the number is not between 0 and 100, this inner loop forces the user to re-enter that tank's reading.

• if (levels[i] < 25) { fillCount++; }: Once a valid reading is accepted, it checks if the tank is under 25% and adds 1 to fillCount.

This final section generates the monitoring report, saves a permanent log to a text file, and decides whether to repeat the program. First, it opens report.txt in append mode so new results are added to the bottom without erasing old history. Then, it loops through every tank to display its status on the screen using showRecommendation while simultaneously writing that same status into the file. After logging the total number of tanks needing water and safely closing the file, it displays that count on the screen and asks if the user wants to check again—looping back to the start if they enter 'y' or 'Y', or cleanly ending the program otherwise.

• fp = fopen("report.txt", "a");: Opens (or creates) report.txt in append ("a") mode, ensuring previous check history stays intact at the top of the file.

• for (i = 0; i < n; i++): Steps through all the recorded tanks one by one, printing the tank number and calling showRecommendation(levels[i]) to display the advice on the console.

• if (fp != NULL): Acts as a safety check to make sure the file opened properly before attempting to write to it with fprintf(), preventing the program from crashing if a file error occurs.

• fclose(fp);: Writes the final fillCount summary to the text file and closes it so all saved data is properly flushed and stored on the disk.

• scanf(" %c", &choice); & while (choice == 'y' || choice == 'Y');: Reads the user's answer (the leading space skips any leftover Enter key from earlier inputs) and repeats the entire do-while cycle if they type 'y' or 'Y', or exits via return 0; if they type anything else.
