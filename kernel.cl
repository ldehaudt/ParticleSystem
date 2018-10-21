typedef struct s_particle{
    float x;
    float y;
    float z;
    float vx;
    float vy;
    float vz;
}				particle;

__kernel void initParticles(__global particle *particles, int numParticles, int square) {
 
    int num = get_global_id(0);
 	float x, y, z;

    particles[num].vx = 0;
    particles[num].vy = 0;
    particles[num].vz = 0;
    float r1 = (((int)((num + 1) * 104911.0 / 809.0) % 100000) - 50000) / 50000.0;
    float r2 = (((int)((num + 1) * 1299827.0 / 557.0) % 100000) - 50000) / 50000.0;
    if (square != 0){
        x = r1 / 8.0;
        y = r2 / 8.0;
        z = (((int)((num + 1) * 57947.0 / 971.0) % 100000) - 50000) / 400000.0;
        particles[num].x = x;
        particles[num].y = y;
        particles[num].z = z;
        return;
    }
	double a = r1 * 2 * 3.14;
    double r = 0.5 * sqrt((r2 + 1) / 2);
    particles[num].x = r * cos(a);
    particles[num].y = r * sin(a);
    particles[num].z = 0;
}

__kernel void calcVelo(__global particle *particles, int numParticles, float mouseX, float mouseY) {
 
     int globalNum = get_global_id(0);

    float ax = 0;
    float ay = 0;
    float az = 0;

    float dx = mouseX - particles[globalNum].x;               
    float dy = mouseY - particles[globalNum].y;               
    float dz = 0 - particles[globalNum].z;
    float invr = 1.0 / (dx*dx + dy*dy + dz*dz + 0.000001);
    ax += 0.01 * invr * dx / sqrt(invr);  		
	ay += 0.01 * invr * dy / sqrt(invr);  		
	az += 0.01 * invr * dz / sqrt(invr);
    particles[globalNum].vx += ax;
    particles[globalNum].vy += ay;
    particles[globalNum].vz += az;
}

__kernel void addVelo(__global particle *particles, int numParticles, float scroll, float offX, float offY) {
 
    int num = get_global_id(0);
 	
    particles[num].x += particles[num].vx + offX;
    particles[num].y += particles[num].vy + offY;
    particles[num].z += particles[num].vz;
    particles[num].x *= scroll + 1;
    particles[num].y *= scroll + 1;
    particles[num].z *= scroll + 1;
    particles[num].vx *= 0.995;
    particles[num].vy *= 0.995;
    particles[num].vz *= 0.995;

}

