function [ p, t, y ] = pty( ax, ay, az, mx, my, mz, gx, gy, gz )
p = -atan(ax/az)
t = atan(ay/az)
y = my
end

