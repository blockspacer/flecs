#include <include/api.h>

void Iter(EcsRows *rows) {
    Position *p = ecs_column(rows, Position, 1);
    Velocity *v = ecs_column(rows, Velocity, 2);
    Mass *m = ecs_column(rows, Mass, 3);

    ProbeSystem(rows);

    int i;
    for (i = rows->offset; i < (rows->offset + rows->limit); i ++) {
        p[i].x = 10;
        p[i].y = 20;

        if (v) {
            v[i].x = 30;
            v[i].y = 40;
        }

        if (m) {
            m[i] = 50;
        }
    }
}

void SystemOnFrame_1_type_1_component() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ECS_ENTITY(world, e_1, Position);
    ECS_ENTITY(world, e_2, Position);
    ECS_ENTITY(world, e_3, Position);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.e[2], e_3);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemOnFrame_1_type_3_component() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e_1, Position, Velocity, Mass);
    ECS_ENTITY(world, e_2, Position, Velocity, Mass);
    ECS_ENTITY(world, e_3, Position, Velocity, Mass);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position, Velocity, Mass);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.e[2], e_3);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);
    test_int(ctx.c[1], eVelocity);
    test_int(ctx.s[1], 0);
    test_int(ctx.c[2], eMass);
    test_int(ctx.s[2], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    
    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get_ptr(world, e_2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get_ptr(world, e_3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);


    Mass *m = ecs_get_ptr(world, e_1, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get_ptr(world, e_2, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get_ptr(world, e_3, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    ecs_fini(world);
}

void SystemOnFrame_3_type_1_component() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e_1, Position);
    ECS_ENTITY(world, e_2, Position, Velocity);
    ECS_ENTITY(world, e_3, Position, Mass);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 3);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 1);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.e[2], e_3);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemOnFrame_2_type_3_component() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Rotation);

    ECS_ENTITY(world, e_1, Position, Velocity, Mass);
    ECS_ENTITY(world, e_2, Position, Velocity, Mass);
    ECS_ENTITY(world, e_3, Position, Velocity, Mass, Rotation);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position, Velocity, Mass);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 3);
    test_int(ctx.invoked, 2);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.e[2], e_3);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);
    test_int(ctx.c[1], eVelocity);
    test_int(ctx.s[1], 0);
    test_int(ctx.c[2], eMass);
    test_int(ctx.s[2], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_3, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    
    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get_ptr(world, e_2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get_ptr(world, e_3, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);


    Mass *m = ecs_get_ptr(world, e_1, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get_ptr(world, e_2, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    m = ecs_get_ptr(world, e_3, Mass);
    test_assert(m != NULL);
    test_int(*m, 50);

    ecs_fini(world);
}

void SystemOnFrame_2_type_1_and_1_not() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ECS_ENTITY(world, e_1, Position);
    ECS_ENTITY(world, e_2, Position);
    ECS_ENTITY(world, e_3, Position, Velocity);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position, !Velocity);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 2);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);
    test_int(ctx.c[1], eVelocity);
    test_int(ctx.s[1], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void SystemOnFrame_2_type_2_and_1_not() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ECS_ENTITY(world, e_1, Position, Velocity);
    ECS_ENTITY(world, e_2, Position, Velocity);
    ECS_ENTITY(world, e_3, Position, Velocity, Mass);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position, Velocity, !Mass);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 2);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 3);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.e[1], e_2);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);
    test_int(ctx.c[1], eVelocity);
    test_int(ctx.s[1], 0);
    test_int(ctx.c[2], eMass);
    test_int(ctx.s[2], 0);
    
    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    p = ecs_get_ptr(world, e_2, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    v = ecs_get_ptr(world, e_2, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    ecs_fini(world);
}

void SystemOnFrame_2_type_2_and_2_not() {
    EcsWorld *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Rotation);

    ECS_ENTITY(world, e_1, Position, Velocity);
    ECS_ENTITY(world, e_2, Position, Velocity, Rotation);
    ECS_ENTITY(world, e_3, Position, Velocity, Mass);

    ECS_SYSTEM(world, Iter, EcsOnFrame, Position, Velocity, !Mass, !Rotation);

    SysTestData ctx = {0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 1);

    test_int(ctx.count, 1);
    test_int(ctx.invoked, 1);
    test_int(ctx.system, eIter);
    test_int(ctx.column_count, 4);
    test_null(ctx.param);

    test_int(ctx.e[0], e_1);
    test_int(ctx.c[0], ePosition);
    test_int(ctx.s[0], 0);
    test_int(ctx.c[1], eVelocity);
    test_int(ctx.s[1], 0);
    test_int(ctx.c[2], eMass);
    test_int(ctx.s[2], 0);
    test_int(ctx.c[3], eRotation);
    test_int(ctx.s[3], 0);

    Position *p = ecs_get_ptr(world, e_1, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    Velocity *v = ecs_get_ptr(world, e_1, Velocity);
    test_assert(v != NULL);
    test_int(v->x, 30);
    test_int(v->y, 40);

    ecs_fini(world);
}
