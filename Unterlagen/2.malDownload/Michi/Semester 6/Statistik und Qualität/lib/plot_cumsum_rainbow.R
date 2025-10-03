plot_cumsum_rainbow <- function(data_table, main, xlab, ylab, is_relative = FALSE, scale_factor = 1.1)
{
  # data_table... table to draw
  # main... main title. like in barplot
  # xlab... x axis name
  # ylab... y axis name
  # Set variables for plot 
  data_table.len <- length(data_table)
  colors <- rainbow(data_table.len) 
  space_initial <- 1.4
  space_between <- 1.2
  spacing <- seq(space_initial, length.out = data_table.len, by = space_between)
  
  # Create inital barplot
  barplot(rep(data_table[1], length(data_table)), ylim = c(0,(sum(data_table) * scale_factor)), ylab = ylab, xlab = xlab, main = main, col = colors[1], names.arg = names(data_table))
  
  # Add all data on top of other, change color while doing so
  offset_var <- cumsum(data_table)
  for(loop_outer in (data_table.len - 1) : 1){
    idx <- data_table.len - loop_outer 
    for(loop_inner in 1:loop_outer){
      barplot(data_table[idx + 1], add = TRUE, col = colors[idx+1], 
              offset = offset_var[idx], names.arg = NA, 
              space = spacing[idx + loop_inner - 1])
    }
  }
  # Draw median if is relative. 
  if (is_relative){
    abline(0.5, 0, lty='dashed', col='red')
    abline(0.25, 0, lty='dashed')
    abline(0.75, 0, lty='dashed')
  }
}
