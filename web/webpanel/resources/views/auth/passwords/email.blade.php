@extends('layouts.authenticate')

@section('authTitle', 'Reset Password')

@section('authBody')
<div class="panel-body" style="padding-bottom: 0px;">
    @if (session('status'))
        <div class="alert alert-success">
            {{ session('status') }}
        </div>
    @endif

    <form class="form" role="form" method="POST" action="{{ url('/password/email') }}">
        <fieldset>
        {{ csrf_field() }}

            <div class="form-group{{ $errors->has('email') ? ' has-error' : '' }}">
                <input id="email" type="email" class="form-control" name="email" placeholder="E-Mail" value="{{ old('email') }}" required>

                @if ($errors->has('email'))
                    <span class="help-block">
                        <strong>{{ $errors->first('email') }}</strong>
                    </span>
                @endif
            </div>

            <div class="form-group">
                <button type="submit" class="btn btn-primary btn-block">
                    Send Password Reset Link
                </button>
            </div>
        <fieldset>
    </form>
</div>
@endsection
