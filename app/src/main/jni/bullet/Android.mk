# /*
# Bullet Continuous Collision Detection and Physics Library for Android NDK
# Copyright (c) 2006-2009 Noritsuna Imamura  http://www.siprop.org/
# 
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the use of this software.
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
# */
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := bullet
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/ \
        $(LOCAL_PATH)/BulletCollision/BroadphaseCollision \
        $(LOCAL_PATH)/BulletCollision/CollisionDispatch \
        $(LOCAL_PATH)/BulletCollision/CollisionShapes \
        $(LOCAL_PATH)/BulletCollision/Gimpact \
        $(LOCAL_PATH)/BulletCollision/NarrowPhaseCollision \
        $(LOCAL_PATH)/BulletDynamics/ConstraintSolver \
        $(LOCAL_PATH)/BulletDynamics/Dynamics \
        $(LOCAL_PATH)/BulletDynamics/Vehicle \
        $(LOCAL_PATH)/LinearMath \
        $(LOCAL_PATH)/BulletMultiThreaded
        

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -lm -llog


LOCAL_SRC_FILES := \
        LinearMath/btQuickprof.cpp \
		LinearMath/btGeometryUtil.cpp \
		LinearMath/btAlignedAllocator.cpp \
		LinearMath/btSerializer.cpp \
		LinearMath/btConvexHull.cpp \
		LinearMath/btConvexHullComputer.cpp \
		BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp \
		BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp \
		BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp \
		BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp \
		BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp \
		BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp \
		BulletCollision/NarrowPhaseCollision/btConvexCast.cpp \
		BulletCollision/NarrowPhaseCollision/btPolyhedralContactClipping.cpp \
		BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp \
		BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp \
		BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp \
		BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp \
		BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btCollisionObject.cpp \
		BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btGhostObject.cpp \
		BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp \
		BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp \
		BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp \
		BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp \
		BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp \
		BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp \
		BulletCollision/CollisionDispatch/btManifoldResult.cpp \
		BulletCollision/CollisionDispatch/btCollisionWorld.cpp \
		BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp \
		BulletCollision/CollisionDispatch/btUnionFind.cpp \
		BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp \
		BulletCollision/CollisionShapes/btTetrahedronShape.cpp \
		BulletCollision/CollisionShapes/btShapeHull.cpp \
		BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp \
		BulletCollision/CollisionShapes/btCompoundShape.cpp \
		BulletCollision/CollisionShapes/btConeShape.cpp \
		BulletCollision/CollisionShapes/btConvexPolyhedron.cpp \
		BulletCollision/CollisionShapes/btMultiSphereShape.cpp \
		BulletCollision/CollisionShapes/btUniformScalingShape.cpp \
		BulletCollision/CollisionShapes/btSphereShape.cpp \
		BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp \
		BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp \
		BulletCollision/CollisionShapes/btTriangleMeshShape.cpp \
		BulletCollision/CollisionShapes/btTriangleBuffer.cpp \
		BulletCollision/CollisionShapes/btStaticPlaneShape.cpp \
		BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp \
		BulletCollision/CollisionShapes/btEmptyShape.cpp \
		BulletCollision/CollisionShapes/btCollisionShape.cpp \
		BulletCollision/CollisionShapes/btConvexShape.cpp \
		BulletCollision/CollisionShapes/btConvex2dShape.cpp \
		BulletCollision/CollisionShapes/btConvexInternalShape.cpp \
		BulletCollision/CollisionShapes/btConvexHullShape.cpp \
		BulletCollision/CollisionShapes/btTriangleCallback.cpp \
		BulletCollision/CollisionShapes/btCapsuleShape.cpp \
		BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp \
		BulletCollision/CollisionShapes/btConcaveShape.cpp \
		BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp \
		BulletCollision/CollisionShapes/btBoxShape.cpp \
		BulletCollision/CollisionShapes/btBox2dShape.cpp \
		BulletCollision/CollisionShapes/btOptimizedBvh.cpp \
		BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp \
		BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp \
		BulletCollision/CollisionShapes/btCylinderShape.cpp \
		BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp \
		BulletCollision/CollisionShapes/btStridingMeshInterface.cpp \
		BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp \
		BulletCollision/CollisionShapes/btTriangleMesh.cpp \
		BulletCollision/BroadphaseCollision/btAxisSweep3.cpp \
		BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp \
		BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp \
		BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp \
		BulletCollision/BroadphaseCollision/btDispatcher.cpp \
		BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp \
		BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp \
		BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp \
		BulletCollision/BroadphaseCollision/btDbvt.cpp \
		BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp \
		BulletCollision/Gimpact/btGImpactBvh.cpp \
        BulletCollision/Gimpact/btGImpactQuantizedBvh.cpp \
        BulletCollision/Gimpact/btTriangleShapeEx.cpp \
        BulletCollision/Gimpact/btGImpactCollisionAlgorithm.cpp \
        BulletCollision/Gimpact/btGImpactShape.cpp \
        BulletCollision/Gimpact/gim_box_set.cpp \
        BulletCollision/Gimpact/gim_contact.cpp \
        BulletCollision/Gimpact/gim_memory.cpp \
        BulletCollision/Gimpact/gim_tri_collision.cpp \
        BulletDynamics/Dynamics/btRigidBody.cpp \
		BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp \
		BulletDynamics/Dynamics/Bullet-C-API.cpp \
		BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp \
		BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp \
		BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp \
		BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp \
		BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp \
		BulletDynamics/ConstraintSolver/btTypedConstraint.cpp \
		BulletDynamics/ConstraintSolver/btContactConstraint.cpp \
		BulletDynamics/ConstraintSolver/btSliderConstraint.cpp \
		BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp \
		BulletDynamics/ConstraintSolver/btHingeConstraint.cpp \
		BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp \
		BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp \
		BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp \
		BulletDynamics/Vehicle/btWheelInfo.cpp \
		BulletDynamics/Vehicle/btRaycastVehicle.cpp \
		BulletDynamics/Character/btKinematicCharacterController.cpp \
		BulletSoftBody/btDefaultSoftBodySolver.cpp \
		BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.cpp \
		BulletSoftBody/btSoftBody.cpp \
		BulletSoftBody/btSoftRigidCollisionAlgorithm.cpp \
		BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.cpp \
		BulletSoftBody/btSoftRigidDynamicsWorld.cpp \
		BulletSoftBody/btSoftBodyHelpers.cpp \
		BulletSoftBody/btSoftSoftCollisionAlgorithm.cpp \
		BulletMultiThreaded/SpuCollisionObjectWrapper.cpp \
		BulletMultiThreaded/SpuSampleTask/SpuSampleTask.cpp \
		BulletMultiThreaded/SpuLibspe2Support.cpp \
		BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuContactResult.cpp \
		BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.cpp \
		BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuMinkowskiPenetrationDepthSolver.cpp \
		BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuCollisionShapes.cpp \
		BulletMultiThreaded/btThreadSupportInterface.cpp \
		BulletMultiThreaded/SequentialThreadSupport.cpp \
		BulletMultiThreaded/SpuGatheringCollisionDispatcher.cpp \
		BulletMultiThreaded/Win32ThreadSupport.cpp \
		BulletMultiThreaded/SpuFakeDma.cpp \
		BulletMultiThreaded/PosixThreadSupport.cpp \
		BulletMultiThreaded/SpuCollisionTaskProcess.cpp \
		BulletMultiThreaded/SpuContactManifoldCollisionAlgorithm.cpp \
		BulletMultiThreaded/SpuSampleTaskProcess.cpp \
		BulletMultiThreaded/SpuNarrowPhaseCollisionTask/boxBoxDistance.cpp \
		

include $(BUILD_SHARED_LIBRARY)
