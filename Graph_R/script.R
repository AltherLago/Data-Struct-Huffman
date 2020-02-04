graph <- read.table("out.txt", header = T)
plot(graph$List~graph$element, main="ABB X Lista encadeada", xlab="Valores", ylab="Comparações", col="red")
points(graph$element, graph$Bt, col = "blue")