import csv # Because we need to read the csv file

stid = [] # Store the student id.
name = [] # Store the name.
score = [] # Store the score.

with open('HW2data.csv', newline = '') as csvfile:
    rows = csv.reader(csvfile, delimiter=',') # Because the delimiter in csv is ','.
    headers = next(rows)  # "header" is the name of the first line of the csv.
    # "next" is to move the read pointer to the next line,
    # and the returned data is the data of the current line number.
    for row in rows: # "row" will run row by row in csv file.
        # The row[0] is NO in csv file.
        stid.append(int(row[1])) # Take row[1] to append in stid[].
        name.append(row[2]) # Take row[2] to append in name[].
        # Calculate the score of the HW1~HW3 and turn it to float type.
        temp1 = float(row[3])*0.1 + float(row[4])*0.1 + float(row[5])*0.1
        # Calculate the score of the Midtern and Final and then turn it to float type.
        temp2 = float(row[6])*0.3 + float(row[7])*0.4
        # Plus all score and use round() function (四捨五入).
        # Becaus the range is integar, we need to round the score.
        sc = round((temp1 + temp2), 2) # Take two decimal places.
        score.append(sc) # Append it to score[]
s = "{0:^2}\t{1:^8}\t{2:^6}\t{3:^5}\t{4:^5}" # Format for print.
# The first number in {} represent to number(th),
# and the second number represent to the length of output data.
# "^" represent to center alignment.
print(s.format("NO", "ID", "Name", "Score", "Grade"))
for i in range (10): # Translate the overall score of each student into a grade.
    if round(score[i]) <= 49:
        print(s.format(i+1, stid[i], name[i], score[i], "E"))
    elif round(score[i]) <= 59 and round(score[i]) >= 50:
        print(s.format(i+1, stid[i], name[i], score[i], "D"))
    elif round(score[i]) <= 62 and round(score[i]) >= 60:
        print(s.format(i+1, stid[i], name[i], score[i], "C-"))
    elif round(score[i]) <= 66 and round(score[i]) >= 63:
        print(s.format(i+1, stid[i], name[i], score[i], "C"))
    elif round(score[i]) <= 69 and round(score[i]) >= 67:
        print(s.format(i+1, stid[i], name[i], score[i], "C+"))
    elif round(score[i]) <= 72 and round(score[i]) >= 70:
        print(s.format(i+1, stid[i], name[i], score[i], "B-"))
    elif round(score[i]) <= 76 and round(score[i]) >= 73:
        print(s.format(i+1, stid[i], name[i], score[i], "B"))
    elif round(score[i]) <= 79 and round(score[i]) >= 77:
        print(s.format(i+1, stid[i], name[i], score[i], "B+"))
    elif round(score[i]) <= 84 and round(score[i]) >= 80:
        print(s.format(i+1, stid[i], name[i], score[i], "A-"))
    elif round(score[i]) <= 89 and round(score[i]) >= 85:
        print(s.format(i+1, stid[i], name[i], score[i], "A"))
    elif round(score[i]) <= 100 and round(score[i]) >= 90:
        print(s.format(i+1, stid[i], name[i], score[i], "A+"))
