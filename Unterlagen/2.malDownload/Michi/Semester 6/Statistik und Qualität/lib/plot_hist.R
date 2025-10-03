plot_hist <- function(Data.vec, KlassGrenz.vec, Titel, X_Label)
  # Data.vec ... Datenvektor aus der Urliste
  # KlassGrenz.vec ... Klassengrenzen auf der x-Achse
  # Titel ... Diagrammtitel
  # X_Label ... Beschriftung der x-Achse (Merkmalsachse)
{
  Histo.list <- hist(Data.vec, breaks=KlassGrenz.vec, right=FALSE, plot=FALSE)
  # Zahl auf geeignete Nachkommastellen runden
  Max <- max(Histo.list$density) * 1.25
  Digs <- abs(floor(log10(Max)))
  Ymax <- round(Max, digits=Digs)
  hist(Data.vec, breaks=KlassGrenz.vec, freq=FALSE, right=FALSE, col="blue",
       main=Titel, xlab=X_Label, ylab="Häufigkeitsdichte",
       ylim=c(0,Ymax))
  axis(side=1, at=seq(min(KlassGrenz.vec), max(KlassGrenz.vec), 10))
  text(Histo.list$mids, Histo.list$density+.003, label=c(Histo.list$density), 
       pos=3, cex=.80, srt=45)
  rug(jitter(Data.vec))
  return(Histo.list$density)
}