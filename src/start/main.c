/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:46:27 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/07 08:17:54 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <pthread.h> 
  
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void *myThreadFun(void *value) 
{ 
    sleep(1); 
    printf("Printing GeeksQuiz from Thread \n"); 
    return NULL; 
} 
 
int			main(int ac, char **av)
{
	t_rtv	rtv;
	
    

	if (ac == 2 && strncmp(ft_strrev(av[1]), "vtr.", 4) == 0)
	{
		parce(ft_strrev(av[1]), &rtv);
		if (rtv.camera->check != 1)
			syntax_error(&rtv, ".", "camera parce plz  ", rtv.parse.nb_line);
		setup_mlx(&rtv.mlx);


		pthread_t thread_id;
		pthread_t thread_id0;
		pthread_t thread_id1;
		pthread_t thread_id2;
		pthread_create(&thread_id, NULL, raytracingt, &rtv);
		pthread_create(&thread_id0, NULL, raytracingt0, &rtv);
		pthread_create(&thread_id1, NULL, raytracingt1, &rtv);
		pthread_create(&thread_id2, NULL, raytracingt2, &rtv);

    	pthread_join(thread_id, NULL);
		pthread_join(thread_id0, NULL);
    	pthread_join(thread_id1, NULL);
		pthread_join(thread_id2, NULL);
		//raytracing(&rtv);

		display(&rtv, &rtv.mlx);
	}
	else
		syntax_error(&rtv, ".", "please parse file next time ", 0);
	return (0);
}
