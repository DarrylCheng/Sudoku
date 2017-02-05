data <- read.csv('Results.csv')
str(data)

#Distribution of dimensions
table(data['Dimension'])
data['Solvable..Constraint.Propogation.'] <- NULL
data['Solvable..Backtracking.'] <- NULL
names(data)[9] = "TimeCP"

#Distribution of 9x9 by difficulty
table(data[ data["Dimension"] == "9x9", "Difficulty" ])
table(data[ data["Dimension"] == "12x12", "Difficulty" ])
table(data[ data["Dimension"] == "18x18", "Difficulty" ])


a <- data[which(data["Dimension"] == "9x9" & data["Difficulty"] == "EASY"),]
a <- a[,c(7:9)]
nrow(a)

out <- boxplot.stats(as.vector(a$TimeGenerate))$out
a = a[!sapply(a$TimeGenerate, function(x) x %in% as.vector(out)),]
out <- boxplot.stats(as.vector(a$TimeBT))$out
a = a[!sapply(a$TimeBT, function(x) x %in% as.vector(out)),]
out <- boxplot.stats(as.vector(a$TimeCP))$out
a = a[!sapply(a$TimeCP, function(x) x %in% as.vector(out)),]
ind <- sample(1:nrow(a), 300)
a <- a[ind,]
apply(a,2,function(x) mean(x))





a <- data[which(data["Dimension"] == "9x9" & data["Difficulty"] == "EVIL"),]
a <- a[,c(7:9)]
nrow(a)

out <- boxplot.stats(as.vector(a$TimeGenerate))$out
a = a[!sapply(a$TimeGenerate, function(x) x %in% as.vector(out)),]
out <- boxplot.stats(as.vector(a$TimeBT))$out
a = a[!sapply(a$TimeBT, function(x) x %in% as.vector(out)),]
out <- boxplot.stats(as.vector(a$TimeCP))$out
a = a[!sapply(a$TimeCP, function(x) x %in% as.vector(out)),]
ind <- sample(1:nrow(a), 300)
a <- a[ind,]
apply(a,2,function(x) mean(x))




a <- data[which(data["Dimension"] == "12x12" & data["Difficulty"] == "EASY"),]
a <- a[,c(7:9)]
nrow(a)

out <- boxplot.stats(as.vector(a$TimeGenerate))$out
a = a[!sapply(a$TimeGenerate, function(x) x %in% as.vector(out)),]
ind <- sample(1:nrow(a), 300)
a <- a[ind,]
apply(a,2,function(x) mean(x))



a <- data[which(data["Dimension"] == "12x12" & data["Difficulty"] == "EVIL"),]
a <- a[,c(7:9)]
nrow(a)

out <- boxplot.stats(as.vector(a$TimeGenerate),4)$out
a = a[!sapply(a$TimeGenerate, function(x) x %in% as.vector(out)),]
out <- boxplot.stats(as.vector(a$TimeBT),4)$out
a = a[!sapply(a$TimeBT, function(x) x %in% as.vector(out)),]

ind <- sample(1:nrow(a), 300)
a <- a[ind,]
apply(a,2,function(x) mean(x))


a <- data[which(data["Dimension"] == "18x18" & data["Difficulty"] == "EASY"),]
a <- a[,c(7:9)]
nrow(a)
(out <- boxplot.stats(as.vector(a$TimeGenerate),5)$out)
a = a[!sapply(a$TimeGenerate, function(x) x %in% as.vector(out)),]

apply(a,2,function(x) mean(x))


a <- data[which(data["Dimension"] == "18x18" & data["Difficulty"] == "EVIL"),]
a <- a[,c(7:9)]
nrow(a)

apply(a,2,function(x) mean(x))
