#include<stdio.h>
#include<stdlib.h> 


  int main() {
      
       int i , n , head , disk_size ,total=0;
       
          printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);  
    
      for(int i =0 ; i<n-1 ; i++){
           for(int j=i+1 ; j<n ; j++){
                if(req[i]> req[j]){
                    int temp = req[i];
                    req[i] = req[j];
                    req[j] =  temp ;
                    
                }
               
           }
          
      }
      
      
      
      int index=0;
      for(int i=0 ; i<n ; i++){
          if(head< req[i])
              index = i;
              break;
          
      } 
      
      printf(" c look  of movement ");
      
        for (int i=index; i<n ; i++){
             printf("%d",req[i]) ;
             total +=abs(head - req[i]);
             head = req[i];
            
        }
        
        
        if(index !=0){
            total +=abs(head - req[0]);
            head = req[0];
        }
      
        for (int i=0; i<n ; i++){
             printf("%d",req[i]) ;
             total +=abs(head - req[i]);
             head = req[i];
            
        }
      
       
      
      
      
       printf(" total seek time : %d",total );
      printf("  avrage total seek time : %.2f", (float) total / n );
      
    
    
    
      
      
      
      
     return 0 ;
    
     
     
     
     
     
      
  }