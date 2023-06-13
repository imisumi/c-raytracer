













if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = delta.y * GetRotationSpeed();
		float yawDelta = delta.x * GetRotationSpeed();

		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
			glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
		m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

		moved = true;
	}


	glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
			glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));




			#include <pthread.h>

// Define the number of threads you want to use
#define NUM_THREADS 4

// Define the thread function
void* calculate_ray_direction(void* arg)
{
    t_data* d = (t_data*)arg;

    for (int y = d->image->height - 1; y >= 0; y--)
    {
        for (int x = 0; x < d->image->width; x++)
        {
            // Calculate the ray direction for each pixel
            // (remaining code from your original function goes here)
        }
    }

    pthread_exit(NULL);
}

void recalculate_ray_direction(t_data* d)
{
    // Create an array of threads
    pthread_t threads[NUM_THREADS];

    // Divide the height of the image by the number of threads
    int rows_per_thread = d->image->height / NUM_THREADS;

    // Create and start the threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        // Calculate the start and end rows for each thread
        int start_row = i * rows_per_thread;
        int end_row = start_row + rows_per_thread - 1;

        // Create the thread and pass the relevant data
        pthread_create(&threads[i], NULL, calculate_ray_direction, (void*)d);

        // You may need to handle the case where the height is not evenly divisible by NUM_THREADS
        // In such cases, you can assign the remaining rows to one of the threads or handle it separately.

        // Note: This example assumes that the t_data structure is shared among threads safely.
        // Ensure proper synchronization if there are shared resources that need protection.
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
