data <- read.csv("HW2data.csv")
print(data)
cat("\n")

for(i in c(1:10))
{
    # Score calculation 
    num <- 0
    num <- data[i, 4]*0.1 + data[i, 5]*0.1 + data[i, 6]*0.1 + data[i, 7]*0.3 + data[i, 8]*0.4

    # Grade interval calculation and print
    if(num >= 90) cat(data[i, 3], num, 'A+', sep = "\t")
    else if(round(num) >= 85) cat(data[i, 3], num, 'A', num, sep = "\t")
    else if(round(num) >= 80) cat(data[i, 3], num, 'A-', sep = "\t")
    else if(round(num) >= 77) cat(data[i, 3], num, 'B+', sep = "\t")
    else if(round(num) >= 73) cat(data[i, 3], num, 'B', sep = "\t")
    else if(round(num) >= 70) cat(data[i, 3], num, 'B-', sep = "\t")
    else if(round(num) >= 67) cat(data[i, 3], num, 'C+', sep = "\t")
    else if(round(num) >= 63) cat(data[i, 3], num, 'C', sep = "\t")
    else if(round(num) >= 60) cat(data[i, 3], num, 'C-', sep = "\t")
    else if(round(num) >= 50) cat(data[i, 3], num, 'D', sep = "\t")
    else cat(data[i, 3], num, 'E', sep = "\t")
    cat("\n")
}
