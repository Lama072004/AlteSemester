lorenzkurve <- function(Ressource.vec, Proz, Titel, XLabel, YLabel)
{
  # Ressource.vec ... Vektor, der die Urliste enthält, z.B. c(a1, a2, a3, a4,...)
  # Proz ... Intervall für die Prozentschritte auf der x-Achse, z.B. 0.2
  # Titel ... Diagrammüberschrift
  # XLabel ... x-Achsen-Beschriftung
  # YLabel ... y-Achsen-Beschriftung
  
  Ressource.vec[Ressource.vec < 0] <- 0   # setze alle negativen Einträge auf Null
  Len <- length(Ressource.vec)
  Anteil.vec <- 1:Len / Len
  Ressource.vec <- Ressource.vec[order(Ressource.vec)]
  Ressource.vec <- cumsum(Ressource.vec)
  Ressource.vec <- Ressource.vec / Ressource.vec[Len]
    
  Schrittw <- round(Len * Proz)         #Anz. der Felder/Indizes pro Schritt
  AnzLoop <- floor(Len / Schrittw) - 1  #letzter Loop wird gesondert mit angepasster Länge ausgeführt
  Schritt0 <- Len - Schrittw * AnzLoop  #Anz. der Felder/Indizes für letzten Schritt
    
  X.vec <- rep(0,AnzLoop+2)
  Y.vec <- X.vec
    
  for(i in 1:AnzLoop)
    {
      Idx <- i * Schrittw
      X.vec[i+1] <- Anteil.vec[Idx]
      Y.vec[i+1] <- Ressource.vec[Idx]
    }
  X.vec[AnzLoop+2] <- Anteil.vec[Len]
  Y.vec[AnzLoop+2] <- Ressource.vec[Len]
 
  plot(X.vec, Y.vec, main=Titel, xlab=XLabel, ylab=YLabel, type="l", col="blue")
  points(X.vec,Y.vec)
  lines(c(0,1), c(0,1), lty="dashed")
}
