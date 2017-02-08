@extends('layouts.dashboard')

@section('contentTitle', 'Loo uus kasutaja')

@push('scripts')
	<!-- DataTables JavaScript -->
	<script src="/vendor/datatables/js/jquery.dataTables.min.js"></script>
	<script src="/vendor/datatables-plugins/dataTables.bootstrap.min.js"></script>
	<script src="/vendor/datatables-responsive/dataTables.responsive.js"></script>

	<!-- Tables -->
    <script>
    $(document).ready(function() {
        $('#dataTables').DataTable({
            responsive: true
        });
    });
    </script>
@endpush


@section('content')
<div class="row">
	    <form class="form" role="form" method="POST" action="{{ url('/accounts/store') }}">
	        {{ csrf_field() }}

			<div class="col-lg-3 col-md-6">

		        <div class="form-group{{ $errors->has('name') ? ' has-error' : '' }}">
		            <input id="name" type="text" class="form-control" name="name" placeholder="Name" value="{{ old('name') }}" required autofocus>

		            @if ($errors->has('name'))
		                <span class="help-block">
		                    <strong>{{ $errors->first('name') }}</strong>
		                </span>
		            @endif
		        </div>

		        <div class="form-group{{ $errors->has('email') ? ' has-error' : '' }}">
		            <input id="email" type="email" class="form-control" name="email" placeholder="E-Mail" value="{{ old('email') }}" required>

		            @if ($errors->has('email'))
		                <span class="help-block">
		                    <strong>{{ $errors->first('email') }}</strong>
		                </span>
		            @endif
		        </div>

		        <div class="form-group{{ $errors->has('password') ? ' has-error' : '' }}">
		            <input id="password" type="password" class="form-control" name="password" placeholder="Password" required>

		            @if ($errors->has('password'))
		                <span class="help-block">
		                    <strong>{{ $errors->first('password') }}</strong>
		                </span>
		            @endif
		        </div>

		        <div class="form-group">
		            <input id="password-confirm" type="password" class="form-control" name="password_confirmation" placeholder="Confirm Password" required>
		        </div>

			</div>

	        <div class="form-group col-lg-3 col-md-6">
	            <button type="submit" class="btn btn-lg btn-primary btn-block text-center">
	                Register
	            </button>
	        </div>

	    </form>
</div>
@endsection
