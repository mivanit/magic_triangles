this_round <- 0
for (n in c(1:10000)){
  check_list<-rep(1,n)
  
  curr_ns<-c(n)
  check_list[n]<-0
  
  num_left <- sum(check_list)
  m <- 0
  while (num_left > 0){
    m <- m + 1
    this_round<-c()
    for (curr_n in curr_ns){
      gt0 <- TRUE
      k=0
      nk <- curr_n - (3^k)
      while (nk > 0) {
        if (check_list[nk] > 0){
          this_round<-c(this_round,nk)
          check_list[nk] <- 0
        }
        k <- k+1
        nk <- curr_n - (3^k)
      }
    }
    num_left <- sum(check_list)
    curr_ns <- this_round
  }
  
  out<-c(n,m,this_round,"\n")
  cat(paste(out),sep=',')
}