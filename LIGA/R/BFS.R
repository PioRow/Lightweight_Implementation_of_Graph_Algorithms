#' @useDynLib LIGA
"_PACKAGE"

#' @title 
#' @description
#' 
#'
#' @return
#' 
#'
#' @param 
#' @param 
#'
#' @examples
#' 
#' 
#' 
#' 
#'
#' @export
BFS <- function(g,tgt,srs, return.path=FALSE)
    .Call("BFS",g ,tgt ,srs , return.path, PACKAGE="LIGA")



# R CMD build <folder>  # -> LIGA_0.0.1.tar.gz
# R CMD INSTALL LIGA_0.0.1.tar.gz
# R CMD check LIGA_0.0.1.tar.gz
