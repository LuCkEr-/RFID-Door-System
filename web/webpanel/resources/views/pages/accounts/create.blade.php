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
<form class="form" role="form" method="POST" action="{{ url('/accounts/store') }}">
    {{ csrf_field() }}

	<div class="row">
		<div class="col-lg-4 col-md-6">

	        <div class="form-group{{ $errors->has('firstName') ? ' has-error' : '' }}">
	            <input id="firstName" type="text" class="form-control" name="firstName" placeholder="Eesnimi" value="{{ old('firstName') }}" required autofocus>

	            @if ($errors->has('firstName'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('firstName') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('lastName') ? ' has-error' : '' }}">
	            <input id="lastName" type="text" class="form-control" name="lastName" placeholder="Perekonnanimi" value="{{ old('lastName') }}" required>

	            @if ($errors->has('lastName'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('lastName') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('extraName') ? ' has-error' : '' }}">
	            <input id="extraName" type="text" class="form-control" name="extraName" placeholder="Täiendav nimi" value="{{ old('extraName') }}">

	            @if ($errors->has('extraName'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('extraName') }}</strong>
	                </span>
	            @endif
	        </div>

	        <div class="form-group{{ $errors->has('email') ? ' has-error' : '' }}">
	            <input id="email" type="email" class="form-control" name="email" placeholder="E-Mail" value="{{ old('email') }}">

	            @if ($errors->has('email'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('email') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('personalCode') ? ' has-error' : '' }}">
	            <input id="personalCode" type="personalCode" class="form-control" name="personalCode" placeholder="Isikukood" value="{{ old('personalCode') }}">

	            @if ($errors->has('personalCode'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('personalCode') }}</strong>
	                </span>
	            @endif
	        </div>

		</div>
		<div class="col-lg-4 col-md-6">

			<div class="form-group{{ $errors->has('homeAddress') ? ' has-error' : '' }}">
	            <input id="homeAddress" type="homeAddress" class="form-control" name="homeAddress" placeholder="Kodu address" value="{{ old('homeAddress') }}">

	            @if ($errors->has('homeAddress'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('homeAddress') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('workAddress') ? ' has-error' : '' }}">
	            <input id="workAddress" type="workAddress" class="form-control" name="workAddress" placeholder="Töökoha address" value="{{ old('workAddress') }}">

	            @if ($errors->has('workAddress'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('workAddress') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('homePhone') ? ' has-error' : '' }}">
	            <input id="homePhone" type="homePhone" class="form-control" name="homePhone" placeholder="Kodutelefoni number" value="{{ old('homePhone') }}">

	            @if ($errors->has('homePhone'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('homePhone') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('mobilePhone') ? ' has-error' : '' }}">
	            <input id="mobilePhone" type="mobilePhone" class="form-control" name="mobilePhone" placeholder="Bobiiltelefoni number" value="{{ old('mobilePhone') }}">

	            @if ($errors->has('mobilePhone'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('mobilePhone') }}</strong>
	                </span>
	            @endif
	        </div>

		</div>
		<div class="col-lg-4 col-md-6">

			<div class="form-group{{ $errors->has('jobTitle') ? ' has-error' : '' }}">
	            <input id="jobTitle" type="jobTitle" class="form-control" name="jobTitle" placeholder="Amet" value="{{ old('jobTitle') }}">

	            @if ($errors->has('jobTitle'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('jobTitle') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('employer') ? ' has-error' : '' }}">
	            <input id="employer" type="employer" class="form-control" name="employer" placeholder="Tööandja" value="{{ old('employer') }}">

	            @if ($errors->has('employer'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('employer') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('comments') ? ' has-error' : '' }}">
	            <input id="comments" type="comments" class="form-control" name="comments" placeholder="Commentaarid" value="{{ old('comments') }}">

	            @if ($errors->has('comments'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('comments') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('pan') ? ' has-error' : '' }}">
	            <input id="pan" type="pan" class="form-control" name="pan" placeholder="pan????" value="{{ old('pan') }}">

	            @if ($errors->has('pan'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('pan') }}</strong>
	                </span>
	            @endif
	        </div>

			<div class="form-group{{ $errors->has('businessName') ? ' has-error' : '' }}">
	            <input id="businessName" type="businessName" class="form-control" name="businessName" placeholder="Ärinimi" value="{{ old('businessName') }}">

	            @if ($errors->has('businessName'))
	                <span class="help-block">
	                    <strong>{{ $errors->first('businessName') }}</strong>
	                </span>
	            @endif
			</div>

		</div>
	</div>

	<div class="form-group text-center">
		<button type="submit" class="btn btn-lg btn-primary btn-block ">
			Lisa uus kasutaja
		</button>
	</div>

</form>
@endsection
