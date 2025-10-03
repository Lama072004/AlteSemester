summenhfk <- function(Daten.vec, AnzInterv, main = "Verteilungsfunktion", xlab="", ylab="")
  
  # Daten.vec ... beliebiger Vektor mit Messwerten (z.B. Stablängen, etc.)
  # AnzInterv ... Anzahl der Intervalle im Histogramm
  
{
  y <- hist(Daten.vec,breaks=AnzInterv, plot=F)
  y.br <- y$breaks[-1]
  x.ax.OG <- round(max(Daten.vec)*1.1,0)
  y.br.1 <- c(y$breaks,x.ax.OG)
  y.counts <- cumsum(y$counts)/length(Daten.vec)
  y.counts.1 <- cumsum(c(0,y$counts,0))/length(Daten.vec)
  plot(y.br.1, y.counts.1, type="l", lty=1, main=main , xlab=xlab, ylab=ylab)
  lines(y.br.1,y.counts.1,type="s",lty=3)
  points(y.br,y.counts)
  abline(.5,0,lty="dashed")
}
