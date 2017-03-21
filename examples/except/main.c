#include <stdio.h>
#include "exception_handler.h"
#include "exception.h"

#define EXCEPTION_CODE	0xCAFE

#define EXCEPT(msg) new(Exception, msg, __FILE__, __LINE__)

void	fonction_qui_throw()
{
  printf("avant le throw\n");
  throw(1, EXCEPT("Exception in try(1)"), EXCEPTION_CODE);
  printf("après le throw\n");
}

int main()
{
  try(0)
    {
      printf("Entering the try(0)\n");
      try(1)
	{
	  printf("Entering the try(1)\n");

	  printf("before exception, try(1)\n");
	  fonction_qui_throw();
	  printf("after exception, try(1)\n");
	}
      catch(EXCEPTION_CODE)
      {
	printf("Exception caught level try(1) : %s\n",
	       Exception_to_string(getEx(1)));
	/* Reject the throw in down levels */
	throw(0, getEx(1), EXCEPTION_CODE);
      }
      finally
	{
	  printf("try(1) finally block\n");
	}
      etry;
      printf("before exception, try(0)\n");
      throw(0, EXCEPT("Exception in try(0)"), EXCEPTION_CODE);
      printf("after exception, try(0)\n");
    }
  catch(EXCEPTION_CODE)
  {
    printf("Exception caught level try(0) : %s\n",
	   Exception_to_string(getEx(0)));
  }
  finally
    {
      printf("try(0) Finaly block\n");
    }
  etry;
  return 0;
}
